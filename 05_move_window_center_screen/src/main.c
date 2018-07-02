#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

  int open = 1;

  Display *display;
  Window window;
  XEvent xevent;
  int screen_num;
  Window root_window;
  unsigned long border;
  unsigned long background;
  Screen* screen;
  GC gc;

  display = XOpenDisplay(NULL);

  if (display == NULL) {
    fprintf(stderr, "ERROR: 'Unable to open display.'.");
    return -1;
  }

  screen_num = DefaultScreen(display);
  screen = DefaultScreenOfDisplay(display);

  gc = XDefaultGC(display, screen_num);

  root_window = RootWindow(display, screen_num);

  border = BlackPixel(display, screen_num);
  background = WhitePixel(display, screen_num);

  int window_pos_x = 0;
  int window_pos_y = 0;
  /*int width = XDisplayWidth(display, screen_num);*/

  /*XWindowAttributes root_window_attributes;*/
  /*XGetWindowAttributes(display, root_window, &root_window_attributes);*/

  window = XCreateSimpleWindow(display, root_window, window_pos_x, window_pos_y, 200, 200, 1, border, background);
  XSizeHints *size_hints = XAllocSizeHints();

  size_hints->flags = PMinSize|PMaxSize;
  size_hints->min_width = 200;
  size_hints->min_height = 200;
  size_hints->max_width = 200;
  size_hints->max_height = 200;

  XSelectInput(display, window, ExposureMask|KeyPressMask);

  XSetWMNormalHints(display, window, size_hints);
  /*XGetWindowAttributes(display, window, &window_attributes);*/


  /*XSetWindowAttributes window_attributes;*/
  /*window_attributes.win_gravity = CenterGravity;*/
  /*XChangeWindowAttributes(display, window, PGravity, &window_attributes);*/

  XMapWindow(display, window);

  while (open) 
  {
    XNextEvent(display, &xevent);

    if (xevent.type == Expose) {

      XDrawLine(display, window, gc, 0, 0, 200, 200);

    }

    if (xevent.type == KeyPress) {

      if (xevent.xkey.keycode == 9) {
        open = 0;
      }

    }

  }

  XCloseDisplay(display);

  return 0;
}
