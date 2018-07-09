#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{

  /* IPv4 */

  int port = 17001;

  char ip4[INET_ADDRSTRLEN];
  struct sockaddr_in sa;

  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = INADDR_ANY;
  sa.sin_port = htons(port);

  inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);

  printf("The IPv4 address is: %s.\n", ip4);

  /* IPv6 */

  char ip6[INET6_ADDRSTRLEN];
  struct sockaddr_in6 sa6;

  sa6.sin6_family = AF_INET6;
  sa6.sin6_port = htons(port);

  inet_ntop(AF_INET6, &(sa6.sin6_addr), ip6, INET6_ADDRSTRLEN);

  printf("The IPv6 address is: %s.\n", ip6);

  return 0;
}
