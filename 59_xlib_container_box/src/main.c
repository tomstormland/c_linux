#include <stdio.h>

#include <window.h>
#include <container.h>
#include <box.h>

int main(int argc, char *argv[])
{

  if (M_WindowInitialize(800, 700) == -1) {

    fprintf(stderr, "ERROR: Failed to initialize window.\n");

    return -1;
  }

  M_Container *container = M_MakeContainer(10, 10, window->width - 10 * 2, window->height - 10 * 2);

  M_Box *box_a = M_MakeBox("LOREM TEXT 1");
  M_Box *box_b = M_MakeBox("LOREM TEXT 2");
  M_Box *box_c = M_MakeBox("LOREM TEXT 3");

  M_ContainerAddBox(container, box_a);
  M_ContainerAddBox(container, box_b);
  M_ContainerAddBox(container, box_c);

  while (window->open) {

    while (XPending(window->display)) {
      XNextEvent(window->display, &window->event);

      if (window->event.type == Expose) {

        M_DrawContainer(container);

      } else if (window->event.type == KeyPress) {

        if (window->event.xkey.keycode == 9) {
          window->open = 0;
        }

      }

    }

  }

  return 0;
}
