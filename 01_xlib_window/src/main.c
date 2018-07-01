#include <X11/Xlib.h>
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

  display = XOpenDisplay(NULL);

  if (display == NULL) {
    fprintf(stderr, "ERROR: 'Unable to open display.'.");
    return -1;
  }

  screen = DefaultScreen(display);

  root_window = RootWindow(display, screen);

  border = BlackPixel(display, screen);
  background = WhitePixel(display, screen);

  window = XCreateSimpleWindow(display, root_window, 10, 10, 100, 100, 1, border, background);

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
