#include <window.h>
#include <container.h>
#include <stdio.h>
#include <stdlib.h>

M_Container* M_MakeContainer(int x, int y, unsigned int width, unsigned int height) 
{
  M_Container *container = malloc(sizeof(M_Container));

  container->box_count = 0;

  container->x = x;
  container->y = y;
  container->width = width;
  container->height = height;

  return container;
}

int M_DrawContainer(M_Container *container) 
{
  int i;
  XDrawRectangle(window->display, window->handle, window->gc, container->x, container->y, container->width, container->height);

  for (i=0; i<container->box_count; i++) {
    M_Box *box = container->boxes[i];

    printf("%s.\n", box->text);

    int x = 10 + container->x;
    int y = 10 + container->y + (30+10) * i;
    int width = container->width - 10 * 2;
    int height = 30;

    XDrawRectangle(window->display, window->handle, window->gc, x, y, width, height);
  }
}

int M_ContainerAddBox(M_Container *container, M_Box *box) 
{
  /*container->boxes = (M_Box**)realloc(container->boxes, 42);*/

  /*container->boxes[container->box_count] = box;*/
  /*container->box_count += 1;*/
}
