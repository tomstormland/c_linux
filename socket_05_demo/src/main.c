#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#define STDIN 0 /* file descriptor for standard input */

int main(int argc, char *argv[])
{

  struct timeval tv;
  fd_set readfds;

  /* 2.5 seconds */

  tv.tv_sec = 2;
  tv.tv_usec = 250000;

  FD_ZERO(&readfds);
  FD_SET(STDIN, &readfds);

  /* don't create about writefds and exceptfds */
  select(STDIN+1, &readfds, NULL, NULL, &tv);
  if (FD_ISSET(STDIN, &readfds)) {
    printf("A key was pressed.\n");
  } else {
    printf("Timed out.\n");
  }

  return 0;
}
