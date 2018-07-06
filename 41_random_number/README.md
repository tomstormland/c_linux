41_random_number
================

```c
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  int num;

  srand(time(NULL));

  /* random number between 0 and 9 */
  num = rand() % 10;

  /* random number between 1 and 10 */
  num = rand() % 10 + 1;

  /* random number between 0 and 10 */
  num = rand() % (10 + 1);

  /* random number between 5 and 10 */
  num = rand() % (10 + 1 - 5) + 5;

  /* random number between 5 and 10 */
  num = rand() % 6 + 5;

  return 0;
}
```
