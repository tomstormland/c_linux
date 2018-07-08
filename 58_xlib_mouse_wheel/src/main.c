#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string.h>

struct _Rect {
  int width;
  int height;
  int x;
  int y;
};

int main(int argc, char *argv[]) 
{

  int is_open = 1;

  XSizeHints *size_hints;

  Display *display;
  Window root_window;
  Window window;
  XEvent xevent;
  int screen_num;

  GC gc;

  unsigned int window_width = 800;
  unsigned int window_height = 800;

  unsigned long black_pixel;
  unsigned long white_pixel;

  struct _Rect *rect = malloc(sizeof(struct _Rect));

  rect->width = 20;
  rect->height = 20;
  rect->x = window_width / 2 - rect->width / 2;
  rect->y = window_height / 2 - rect->height / 2;

  display = XOpenDisplay(NULL);
  if (display == NULL) {
    fprintf(stderr, "ERROR: Failed to open display.\n");
    return -1;
  }

  screen_num = DefaultScreen(display);

  gc = DefaultGC(display, screen_num);

  black_pixel = BlackPixel(display, screen_num);
  white_pixel = WhitePixel(display, screen_num);

  root_window = RootWindow(display, screen_num);

  size_hints = XAllocSizeHints();
  size_hints->flags = PMinSize|PMaxSize;
  size_hints->min_width = window_width;
  size_hints->min_height = window_width;
  size_hints->max_width = window_width;
  size_hints->max_height = window_width;

  window = XCreateSimpleWindow(display, root_window, 0, 0, window_width, window_height, 1, black_pixel, white_pixel);

  XSetWMNormalHints(display, window, size_hints);

  XSelectInput(display, window, ExposureMask|KeyPressMask|ButtonPressMask);

  XMapWindow(display, window);

  while (is_open) {

    while (XPending(display)) {
      XNextEvent(display, &xevent);

      if (xevent.type == Expose) {

        /* draw rect */
        XFillRectangle(display, window, gc, rect->x, rect->y, rect->width, rect->height);

        char message[] = "LOREM TEXT";
        XDrawString(display, window, gc, 10, 20, message, strlen(message));

      }

      if (xevent.type == ButtonPress) {

        /* clear last rect position area */
        XClearArea(display, window, rect->x, rect->y, rect->width, rect->height, 0);

        /* mouse wheel handle */
        if (xevent.xbutton.button == 4) {
          /* scrolling up */
          if (rect->y > 0) {
            rect->y -= 50;
          } else {
            rect->y = 0;
          }
        } else if (xevent.xbutton.button == 5) {
          /* scrolling down */
          if (rect->y < window_height - rect->width) {
            rect->y += 50;
          } else {
            rect->y = window_height - rect->width;
          }
        }

        /* draw rect again */
        XFillRectangle(display, window, gc, rect->x, rect->y, rect->width, rect->height);

      }

      if (xevent.type == KeyPress) {
        switch (xevent.xkey.keycode) {
          case 9: goto cleanup; break;
        }
      }

    }

  }

cleanup: 

  XCloseDisplay(display);

  return 0;
}
