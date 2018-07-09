/* client */

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

#define MAXDATASIZE 100 /* max num bytes we can get at once */

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

  int sockfd;
  int rv;
  struct addrinfo hints;
  struct addrinfo *servinfo;
  struct addrinfo *p;
  const char *port = "17001";
  char s[INET6_ADDRSTRLEN];
  char buf[MAXDATASIZE];
  int numbytes;

  memset(&hints, 0, sizeof(hints));

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  rv = getaddrinfo("127.0.0.1", port, &hints, &servinfo);

  if (rv != 0) {
    fprintf(stderr, "ERROR: Was unable to load address information: %s.\n", gai_strerror(rv));
    return -1;
  }

  /* loop throught all the results and connect to the first we can */
  for (p = servinfo; p != NULL; p = p->ai_next) {
    sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (sockfd == -1) {
      fprintf(stderr, "ERROR: Was unable to create socket, continuing.\n");
      continue;
    }

    rv = connect(sockfd, p->ai_addr, p->ai_addrlen);
    if (rv == -1) {
      close(sockfd);
      fprintf(stderr, "ERROR: Was unable to connect to server.\n");
      continue;
    }

    break;
  }

  if (p == NULL) {
    fprintf(stderr, "ERROR: Was unable to connect to server.\n");
    return -1;
  }

  inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof(s));

  printf("Connecting to %s.\n", s);

  freeaddrinfo(servinfo); /* all done with this structure */

  numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0);

  if (numbytes == -1) {
    fprintf(stderr, "ERROR: Was unable to recv.\n");
    return -1;
  }

  buf[numbytes] = '\0';

  printf("Received '%s'.\n", buf);

  close(sockfd);

  return 0;
}
