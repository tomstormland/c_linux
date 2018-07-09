#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char *argv[])
{

  int status;
  char ipstr[INET6_ADDRSTRLEN];
  struct addrinfo hints;
  struct addrinfo *res, *p;

  memset(&hints, 0, sizeof(hints)); /* make sure the struct is empty */

  hints.ai_family = AF_UNSPEC; /* do not care IPv4 or IPv6 */
  hints.ai_socktype = SOCK_STREAM; /* TCP stream sockets */
  hints.ai_flags = AI_PASSIVE; /* fill in IP for me */

  status = getaddrinfo("www.google.com", "3490", &hints, &res);

  if (status != 0) {
    fprintf(stderr, "ERROR: Was unable to get address info: %s.\n", gai_strerror(status));
    return -1;
  }

  for (p=res; p!=NULL; p=p->ai_next) {
    void *addr;
    char *ipver;

    if (p->ai_family == AF_INET) {
      struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
      addr = &(ipv4->sin_addr);
      ipver = "IPv4";
    } else {
      struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
      addr = &(ipv6->sin6_addr);
      ipver = "IPv6";
    }

    /* convert the IP to a string and print it */
    inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));

    printf("%s: %s\n", ipver, ipstr);
  }

  freeaddrinfo(res);

  /* free the info */
  return 0;
}
