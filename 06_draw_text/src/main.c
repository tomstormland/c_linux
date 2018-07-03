#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

int is_open = 1;

unsigned int window_width = 400;
unsigned int window_height = 400;

XEvent xevent;
Display* display;
int screen_num;
Window window;
Window root_window;
unsigned int white_pixel;
unsigned int black_pixel;
XSizeHints* size_hints;
GC gc;

char * text = "Tom Stormland";

int main(int argc, char *argv[]) {

  display = XOpenDisplay(NULL);

  if (display == NULL) {
    printf("ERROR: 'Unable to open display.'.\n");
    return -1;
  }

  screen_num = DefaultScreen(display);

  root_window = RootWindow(display, screen_num);

  white_pixel = WhitePixel(display, screen_num);
  black_pixel = BlackPixel(display, screen_num);

  gc = DefaultGC(display, screen_num);

  window = XCreateSimpleWindow(display, root_window, 0, 0, window_width, window_height, 0, black_pixel, white_pixel);

  XSelectInput(display, window, ExposureMask|KeyPressMask);

  size_hints = XAllocSizeHints();

  size_hints->flags = PMinSize|PMaxSize;
  size_hints->min_width = window_width;
  size_hints->min_height = window_height;
  size_hints->max_width = window_width;
  size_hints->max_height = window_height;
  XSetWMNormalHints(display, window, size_hints);

  XMapWindow(display, window);

  while (is_open) {

    XNextEvent(display, &xevent);

    if (xevent.type == Expose) {
      XDrawString(display, window, gc, 10, 20, text, strlen(text));
    }

    if (xevent.type == KeyPress) {
      if (xevent.xkey.keycode == 9) {
        is_open = 0;
      }
    }

  }

  XDestroyWindow(display, window);
  XCloseDisplay(display);

  return 0;
}
