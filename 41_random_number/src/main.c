#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  srand(time(NULL));

  int num = rand();

  printf("RANDOM NUMBER: %d\n", num);

  /* random number between 0 and 19 */
  num = rand() % 20;

  printf("RANDOM [0-19]: %d\n", num);

  /* num = rand % (max + 1 - min) + min */

  /* random number between 0 and 65 */
  num = rand() % (65 + 1 - 0) + 0;
  printf("RANDOM [0-65]: %d\n", num);

  /* random number between 1 and 10 */
  num = rand() % 10 + 1;
  printf("RANDOM [1-10]: %d\n", num);

  return 0;
}
