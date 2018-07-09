/* server */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <sys/wait.h>

#include <signal.h>

#include <errno.h>

void signal_child_handler(int s)
{
  /* waitpid() might overwrite errno, so we save and restore it */
  int saved_errno = errno;

  while (waitpid(-1, NULL, WNOHANG) > 0);

  errno = saved_errno;
}

/* get sockaddr, IPv4 or IPv6: */
void *get_in_addr(struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in*)sa)->sin_addr);
  }

  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{

  struct sockaddr_storage their_addr; /* connector's address information */
  int server_socket_fd;
  int new_socket_fd;
  struct addrinfo hints;
  socklen_t sin_size;
  int rv;
  const char *port = "17001";
  struct addrinfo *servinfo;
  struct addrinfo *p;
  int yes = 1;
  int BACKLOG = 10;
  struct sigaction sa;
  char s[INET6_ADDRSTRLEN];

  memset(&hints, 0, sizeof(hints));

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE; /* use my ip */

  rv = getaddrinfo(NULL, port, &hints, &servinfo);

  if (rv != 0) {
    fprintf(stderr, "ERROR: Was unable to get address info: %s.\n", gai_strerror(rv));
    return -1;
  }

  /* loop through all the results and bind to the first we can */
  for (p = servinfo; p != NULL; p = p->ai_next) {
    server_socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

    if (server_socket_fd == -1) {
      fprintf(stderr, "ERROR: Was unable to create socket, continuing.\n");
      continue;
    }

    rv = setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    if (rv != 0) {
      fprintf(stderr, "ERROR: Was unable to set socket option.\n");
      return -1;
    }

    rv = bind(server_socket_fd, p->ai_addr, p->ai_addrlen);

    if (rv == -1) {
      fprintf(stderr, "ERROR: Was unable to bind socket.\n");
      return -1;
    }

    break;
  }

  /* all done with server info structure */
  freeaddrinfo(servinfo);

  if (p == NULL) {
    fprintf(stderr, "ERROR: Server was unable to bind.\n");
    return -1;
  }

  rv = listen(server_socket_fd, BACKLOG);

  if (rv == -1) {
    fprintf(stderr, "ERROR: Server socket was unable to listen.\n");
    return -1;
  }

  sa.sa_handler = signal_child_handler; /* reap all dead processes */
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;

  rv = sigaction(SIGCHLD, &sa, NULL);

  if (rv == -1) {
    fprintf(stderr, "ERROR: Problem with sigaction.\n");
    return -1;
  }

  printf("Server is waiting for connections...\n");

  while (1) {

    sin_size = sizeof(their_addr);

    new_socket_fd = accept(server_socket_fd, (struct sockaddr *)&their_addr, &sin_size);

    if (new_socket_fd == -1) {
      fprintf(stderr, "ERROR: Server was unable to accept connection.\n");
      continue;
    }

    inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof(s));

    printf("Got connection from %s.\n", s);

    if (!fork()) { /* this is the child process */
      close(server_socket_fd); /* child does not need the listener */
      rv = send(new_socket_fd, "LOREM TEXT", strlen("LOREM TEXT"), 0);
      if (rv == -1) {
        fprintf(stderr, "ERROR: Was unable to send.\n");
      }
      close(new_socket_fd);
      return 0;
    }

    close(new_socket_fd); /* parent does not need this */
  }

  return 0;
}
