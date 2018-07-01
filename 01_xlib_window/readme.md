01_xlib_window
==============

```c

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(...) 
{
  XEvent xevent;

  Display *display = XOpenDisplay(NULL);

  if (display == NULL) {
    // unable to open display
  }

  int screen = DefaultScreen(display);

  Window root_window = RootWindow(display, screen);

  unsigned int border = BlackPixel(display, screen);
  unsigned int background = WhitePixel(display, screen);

  Window window = XCreateSimpleWindow(display, root_window, 10, 10, 100, 100, 1, border, background);

  XSelectInput(display, window, ExposureMask | KeyPressMask);

  XMapWindow(display, window);

  while (1) 
  {
    XNextEvent(display, &xevent);

    if (xevent.type == Expose) {
      XFillRectangle(...);
      XDrawString(...);
    }

    if (xevent.type == KeyPress) {
      break
    }
  }

  XCloseDisplay(display);

  return 0;
}

```
