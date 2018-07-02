#include <stdio.h>

int main(int argc, char *argv[]) {

  int i, m=0, rows = 10, space;

  for (i=1; i<=rows; i++, m=0) {
    for (space=1; space<=rows-i; space++) {
      printf(" ");
    }
    while (m != 2*i-1) {
      printf("* ");
      m++;
    }

    printf("\n");
  }

  return 0;
}
