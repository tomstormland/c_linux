#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

  Display *display;
  Window window;
  XEvent xevent;
  int screen;
  Window root_window;
  unsigned long border;
  unsigned long background;
  XSizeHints *size_hints;

  display = XOpenDisplay(NULL);

  if (display == NULL) {
    fprintf(stderr, "ERROR: 'Unable to open display.'.");
    return -1;
  }

  screen = DefaultScreen(display);

  root_window = RootWindow(display, screen);

  border = BlackPixel(display, screen);
  background = WhitePixel(display, screen);

  size_hints = XAllocSizeHints();
  size_hints->flags = PMinSize|PMaxSize;
  size_hints->min_width = 400;
  size_hints->min_height = 400;
  size_hints->max_width = 400;
  size_hints->max_height = 400;

  window = XCreateSimpleWindow(display, root_window, 0, 0, 400, 400, 1, border, background);

  XSetWMNormalHints(display, window, size_hints);

  XSelectInput(display, window, ExposureMask|KeyPressMask);

  XMapWindow(display, window);

  while (1) 
  {
    XNextEvent(display, &xevent);

    if (xevent.type == Expose) {

    }

    if (xevent.type == KeyPress) {
      break;
    }

  }

  XCloseDisplay(display);

  return 0;
}
