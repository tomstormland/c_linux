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
#define MAXBUFLEN 100

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
  struct addrinfo hints;
  struct addrinfo *servinfo;
  struct addrinfo *p;
  int rv;
  int numbytes;
  struct sockaddr_storage their_addr;
  char buf[MAXBUFLEN];
  socklen_t addr_len;
  char s[INET6_ADDRSTRLEN];

  memset(&hints, 0, sizeof hints);

  hints.ai_family = AF_UNSPEC; /* set to AF_UNSPECT to force IPv4 */
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE; /* use my ip */

  rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo);

  if (rv != 0) {
    fprintf(stderr, "ERROR: Was unable to get address info: %s.\n", gai_strerror(rv));
    return -1;
  }

  /* loop through all the results and bind to the first we can  */
  for (p = servinfo; p != NULL; p = p->ai_next) {
    sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (sockfd == -1) {
      fprintf(stderr, "ERROR: Was unable to create socket.\n");
      continue;
    }

    rv = bind(sockfd, p->ai_addr, p->ai_addrlen);
    if (rv == -1) {
      fprintf(stderr, "ERROR: Was unable to bind socket.\n");
      continue;
    }

    break;
  }

  if (p == NULL) {
    fprintf(stderr, "ERROR: Was unable to bind socket.\n");
    return -1;
  }

  freeaddrinfo(servinfo);

  printf("Waiting for recvfrom...\n");

  addr_len = sizeof their_addr;

  numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1, 0, (struct sockaddr *)&their_addr, &addr_len);

  if (numbytes == -1) {
    fprintf(stderr, "ERROR: Was unable to recvfrom.\n");
    return -1;
  }

  printf("Received packet from %s.\n", inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s));

  buf[numbytes] = '\0';

  printf("Packet contains '%s'.\n", buf);

  close(sockfd);

  return 0;
}
