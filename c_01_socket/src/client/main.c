/* client */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int i;
  int port = 17001;
  struct sockaddr_in address;
  struct sockaddr_in server_address;
  int client_sock_fd;
  char buffer[1024] = { 0 };
  char text[1024] = { 0 };

  /* create the client socket */
  client_sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (client_sock_fd < 0) {
    fprintf(stderr, "ERROR: Was unable to create client socket.\n");
    return -1;
  }

  memset(&server_address, '0', sizeof(server_address));

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);

  /* TODO: Name this section. */
  i = inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

  if (i <= 0) {
    fprintf(stderr, "ERROR: Invalid address. Address not supported.\n");
    return -1;
  }

  /* connect to server socket */
  i = connect(client_sock_fd, (struct sockaddr *)&server_address, sizeof(server_address));

  if (i < 0) {
    fprintf(stderr, "ERROR: Was unable to connect to server socket.\n");
    return -1;
  }

  sprintf(text, "THIS IS AN IMPORTANT MESSAGE");

  send(client_sock_fd, text, strlen(text), 0);

  printf("Sent: %s.\n", text);

  i = read(client_sock_fd, buffer, 1024);

  printf("Received: %s.\n", buffer);

  return 0;
}
