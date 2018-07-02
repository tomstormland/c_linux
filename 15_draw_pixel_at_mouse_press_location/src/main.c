#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

struct Interface {
  int open;
  int window_x;
  int window_y;
  XSizeHints *size_hints;
  unsigned int window_width;
  unsigned int window_height;
  unsigned int window_border;
  unsigned int window_background;
  unsigned int window_border_width;
  Window window;
  Window root_window;
  XEvent xevent;
  Display *display;
  int screen_num;
  GC gc;
};

int interface_initialize(struct Interface *self) {

  /* initialize interface variables */
  self->open = 1;

  /* setup display */
  self->display = XOpenDisplay(NULL);

  if (self->display == NULL) {
    printf("ERROR: 'Unable to open display.'.\n");
    return -1;
  }

  /* set up screen number */
  self->screen_num = DefaultScreen(self->display);

  /* set up root window */
  self->root_window = RootWindow(self->display, self->screen_num);

  /* set up window */
  self->window_border = BlackPixel(self->display, self->screen_num);
  self->window_background = WhitePixel(self->display, self->screen_num);
  self->window_x = 0;
  self->window_y = 0;
  self->window_width = 400;
  self->window_height = 400;
  self->window_border_width = 2;

  /* set up size hints */
  self->size_hints = XAllocSizeHints();
  self->size_hints->flags = PMinSize|PMaxSize;
  self->size_hints->min_width = self->window_width;
  self->size_hints->min_height = self->window_width;
  self->size_hints->max_width = self->window_width;
  self->size_hints->max_height = self->window_width;

  self->window = XCreateSimpleWindow(self->display, self->root_window, self->window_x, self->window_y, self->window_width, self->window_height, self->window_border_width, self->window_border, self->window_background);

  XSetWMNormalHints(self->display, self->window, self->size_hints);

  XSelectInput(self->display, self->window, ExposureMask|KeyPressMask|ButtonPressMask|ButtonReleaseMask);

  XMapWindow(self->display, self->window);

  /* create / set up graphic contexts */
  self->gc = XCreateGC(self->display, self->window, 0, NULL);

  XSetForeground(self->display, self->gc, self->window_border);

  return 0;
}

int interface_destroy(struct Interface *self) {
  XCloseDisplay(self->display);

  return 0;
}

int interface_main_loop(struct Interface *self) {

  while (self->open) {
    XNextEvent(self->display, &self->xevent);

    if (self->xevent.type == Expose) {

    }

    if (self->xevent.type == ButtonPress) {

      if (self->xevent.xbutton.button == 1) {
        int x = self->xevent.xbutton.x;
        int y = self->xevent.xbutton.y;
        XDrawPoint(self->display, self->window, self->gc, x, y);
      }

    }

    if (self->xevent.type == ButtonRelease) {

      if (self->xevent.xbutton.button == 1) {

      }

    }

    if (self->xevent.type == KeyPress) {

      if (self->xevent.xkey.keycode == 9) {
        self->open = 0;
      }

    }

  }

  interface_destroy(self);

  return 0;
}

int main()
{

  struct Interface interface;

  if (interface_initialize(&interface) == -1) {
    return -1;
  }

  return interface_main_loop(&interface);
}
