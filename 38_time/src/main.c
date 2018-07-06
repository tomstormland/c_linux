#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {

  int msec = 0, tick = 0;

  clock_t start = clock();

  while (tick <= 300000000) {

    if (tick % 10000000 == 0) {
      printf("Tick: %d\n", tick);
    }

    tick += 1;
  }

  clock_t now = clock();

  clock_t difference = now - start;

  msec = difference * 1000 / CLOCKS_PER_SEC;

  printf("Time taken: %d (sec) %d (msec)\n", msec/1000, msec%1000);

  return 0;
}
