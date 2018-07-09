/* server */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char *argv[])
{

  int port = 17001;
  int i;
  int server_socket_fd;
  int new_socket_fd;
  int opt = 1;
  int address_len;
  struct sockaddr_in address;
  char buffer[1024] = { 0 };
  char text[1024] = { 0 };

  address_len = sizeof(address);

  /* create socket file descriptor */
  server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (server_socket_fd == 0) {
    fprintf(stderr, "ERROR: Failed to create server socket..\n");
    return -1;
  }

  /* forcefully attack socket to port 17001 */
  i = setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &opt, sizeof(opt));

  if (i == -1) {
    fprintf(stderr, "ERROR: Failed to set server socket option.\n");
    return -1;
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  /* bind server socket */
  i = bind(server_socket_fd, (struct sockaddr *)&address, sizeof(address));
  if (i == -1) {
    fprintf(stderr, "ERROR: Failed to bind server socket.\n");
    return -1;
  }

  /* server socket listen */
  i = listen(server_socket_fd, 3);

  if (i == -1) {
    fprintf(stderr, "ERROR: Server socket failed to listen.\n");
    return -1;
  }

  printf("Socket server is listening at 127.0.0.1:17001.\n");

  /* server socket accept */
  new_socket_fd = accept(server_socket_fd, (struct sockaddr *)&address, (socklen_t*)&address_len);

  if (new_socket_fd < 0) {
    fprintf(stderr, "ERROR: Was unable to accept new socket.\n");
    return -1;
  }

  i = read(new_socket_fd, buffer, 1024);

  sprintf(text, "I RECEIVED YOUR MESSAGE, THANKS");

  send(new_socket_fd, text, strlen(text), 0);

  return 0;
}
