#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

  pid_t pid;

  /* spawn child to run the program */

  pid = fork();

  if (pid == -1) {
    printf("ERROR: Fork error.\n");
    return -1;
  }

  if (pid == 0) { /* child process */

    char *argv[] = { "../00_test_window/00_test_window", NULL};

    execv("../00_test_window/00_test_window", argv);

  } else { /* parent process */
    waitpid(pid, 0, 0); /* wait for child to exit */
  }

  return 0;
}
