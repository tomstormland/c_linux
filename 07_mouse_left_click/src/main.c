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
  int screen;
  Window root_window;
  unsigned long border;
  unsigned long background;
  GC gc;

  display = XOpenDisplay(NULL);

  if (display == NULL) {
    fprintf(stderr, "ERROR: 'Unable to open display.'.");
    return -1;
  }

  screen = DefaultScreen(display);

  gc = XDefaultGC(display, screen);

  root_window = RootWindow(display, screen);

  border = BlackPixel(display, screen);
  background = WhitePixel(display, screen);

  window = XCreateSimpleWindow(display, root_window, 10, 10, 200, 200, 1, border, background);

  XSizeHints *size_hints = XAllocSizeHints();

  size_hints->flags = PMinSize|PMaxSize;
  size_hints->min_width = 200;
  size_hints->min_height = 200;
  size_hints->max_width = 200;
  size_hints->max_height = 200;


  XSelectInput(display, window, ExposureMask|KeyPressMask|ButtonPressMask);

  XSetWMNormalHints(display, window, size_hints);

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

    if (xevent.type == ButtonPress) {

      if (xevent.xbutton.button == 1) {
        printf("BUTTON PRESSED\n");
      }

    }

  }

  XCloseDisplay(display);

  return 0;
}
