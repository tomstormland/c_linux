27_glad_test
============

https://github.com/Dav1dde/glad

Install glad
------------
pip install --upgrade git+https://github.com/dav1dde/glad.git#egg=glad

Generate loader
----------------
glad --generator=c --out-path=GL

```c
#include <stdio.h>
#include <glad/glad.h>

int main(int argc, char *argv[]) {

  /* set up the context */

  if (!gladLoadGL()) {
    printf("ERROR: 'Unable to load OpenGL'.");
    return -1;
  }

  printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

  return 0;
}
```
