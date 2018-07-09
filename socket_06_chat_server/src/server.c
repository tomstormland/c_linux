/* server */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT "17001"

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in*)sa)->sin_addr);
  }

  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[]) 
{
  int i, j;

  int yes = 1;

  int rv;

  int fdmax;

  int listener_fd;
  int newfd;

  fd_set master; /* master file descriptor list */
  fd_set read_fds; /* temp file descriptor list for select() */

  struct addrinfo hints;
  struct addrinfo *ai;
  struct addrinfo *p;

  socklen_t addrlen;
  struct sockaddr_storage remoteaddr;

  char remoteIP[INET6_ADDRSTRLEN];

  int nbytes;
  char buf[256];

  FD_ZERO(&master); /* clear the master and temp sets */
  FD_ZERO(&read_fds);

  /* get us a socket and bind it */
  memset(&hints, 0, sizeof hints);

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  rv = getaddrinfo(NULL, PORT, &hints, &ai);

  if (rv != 0) {
    fprintf(stderr, "ERROR: Was unable to load address info: %s.\n", gai_strerror(rv));
    return -1;
  }

  for (p = ai; p!= NULL; p = p->ai_next) {
    listener_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (listener_fd < 0) {
      continue;
    }
    /* lose the 'address already in use' error message */
    setsockopt(listener_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    rv = bind(listener_fd, p->ai_addr, p->ai_addrlen);

    if (rv < 0) {
      close(listener_fd);
      continue;
    }

    break;
  }

  /* if we got here, we did not get bound */
  if (p == NULL) {
    fprintf(stderr, "ERROR: Failed to bind.\n");
    return -1;
  }

  freeaddrinfo(ai);

  rv = listen(listener_fd, 10);

  if (rv == -1) {
    fprintf(stderr, "ERROR: Was unable to listen.\n");
    return -1;
  }

  /* add the listener to the master set */
  FD_SET(listener_fd, &master);

  /* keep track of the biggest file descriptor */
  fdmax = listener_fd; /* so far, it's this one */

  for (;;) {
    read_fds = master; /* copy it */

    printf("Waiting for select...\n");
    rv = select(fdmax+1, &read_fds, NULL, NULL, NULL);
    if (rv == -1) {
      fprintf(stderr, "ERROR: Was unable to select.\n");
      return -1;
    }

    /* run through the existing connections looking for data to read */
    for (i=0; i<= fdmax; i++) {
      rv = FD_ISSET(i, &read_fds);

      if (rv) { /* we got this one ? */
        if (i == listener_fd) {
          /* handle new connections */
          addrlen = sizeof remoteaddr;
          newfd = accept(listener_fd, (struct sockaddr *)&remoteaddr, &addrlen);
          if (newfd == -1) {
            fprintf(stderr, "ERROR: Was unable to accept.\n");
          } else {
            FD_SET(newfd, &master); /* add to master set */
            if (newfd > fdmax) { /* keep track of the max */
              fdmax = newfd;
            }
            printf("New connection from %s on socket %d.\n", inet_ntop(remoteaddr.ss_family, get_in_addr((struct sockaddr*)&remoteaddr), remoteIP, INET6_ADDRSTRLEN), newfd);
          }
        } else {
          /* handle data from a client */
          nbytes = recv(i, buf, sizeof buf, 0);
          if (nbytes <= 0) {
            /* error or connection closed by client */
            if (nbytes == 0) {
              /* connection closed */
              printf("Socket %d hung up.\n", i);
            } else {
              fprintf(stderr, "ERROR: Was unable to recv.\n");
            }
            close(i); /* bye */
            FD_CLR(i, &master); /* remove from master set */
          } else {
            /* we received some data from a client */
            for (j = 0; j<= fdmax; j++) {
              /* send to everyone */
              if (FD_ISSET(j, &master)) {
                /* except the listener_fd and ourself */
                if (j != listener_fd && j != i) {
                  rv = send(j, buf, nbytes, 0);
                  if (rv == -1) {
                    fprintf(stderr, "ERROR: Was unable to send.\n");
                  }
                }
              }
            }
          }
        } /* end handle data from client */
      } /* end new incomfing connection */
    } /* end loop throught file descriptors */
  } /* end main loop */

  return 0;
}
