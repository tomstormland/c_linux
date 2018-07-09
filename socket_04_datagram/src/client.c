#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MYPORT "17001"

int main(int argc, char *argv[])
{

  int sockfd;
  struct addrinfo hints;
  struct addrinfo *servinfo;
  struct addrinfo *p;
  int rv;
  int numbytes;

  memset(&hints, 0, sizeof hints);

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;

  rv = getaddrinfo("127.0.0.1", MYPORT, &hints, &servinfo);

  if (rv != 0) {
    fprintf(stderr, "ERROR: Was unable to load address info: %s.\n", gai_strerror(rv));
    return -1;
  }

  /* loop throught all the resuls and make a socket */
  for (p = servinfo; p != NULL; p = p->ai_next) {
    sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (sockfd == -1) {
      fprintf(stderr, "ERROR: Was unable to create socket, continuing.\n");
      continue;
    }

    break;
  }

  if (p == NULL) {
    fprintf(stderr, "ERROR: Was unable to create socket.\n");
    return -1;
  }

  numbytes = sendto(sockfd, "LOREM TEXT", strlen("LOREM TEXT"), 0, p->ai_addr, p->ai_addrlen);

  if (numbytes == -1) {
    fprintf(stderr, "ERROR: Was unable to sendto server.\n");
    return -1;
  }

  freeaddrinfo(servinfo);

  printf("Sent %d bytes to %s.\n", numbytes, "127.0.0.1");

  close(sockfd);

  return 0;
}
