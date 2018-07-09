#ifndef MY_CONTAINER_H
#define MY_CONTAINER_H

#include <box.h>

struct _M_Container {
  M_Box **boxes;
  int box_count;
  int x;
  int y;
  unsigned int width;
  unsigned int height;
};

typedef struct _M_Container M_Container;

M_Container* M_MakeContainer(int x, int y, unsigned int width, unsigned int height);
int M_DrawContainer(M_Container *container);
int M_ContainerAddBox(M_Container *container, M_Box *box);

#endif
