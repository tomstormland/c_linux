```
*
* *
* * *
* * * *
* * * * *
```

```c
#include <stdio.h>

int main(int argc, char *argv[]) {

  int i, j, rows = 5;

  for (i=0; i<=rows; i++) {
    for (j=1; j<=i; j++) {
      printf("* ");
    }
    printf("\n");
  }

  return 0;
}
```
