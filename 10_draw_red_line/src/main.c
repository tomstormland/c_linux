#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

struct Interface {
  int open;
  int window_x;
  int window_y;
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
  Colormap colormap;
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

  self->window = XCreateSimpleWindow(self->display, self->root_window, self->window_x, self->window_y, self->window_width, self->window_height, self->window_border_width, self->window_border, self->window_background);

  /* create / set up colormap */
  self->colormap = DefaultColormap(self->display, 0);

  /* create / set up graphic contexts */
  self->gc = XCreateGC(self->display, self->window, 0, NULL);

  /* set up window hints */
  XSizeHints *size_hints = XAllocSizeHints();
  size_hints->flags = PMaxSize|PMinSize;
  size_hints->min_width = self->window_width;;
  size_hints->min_height = self->window_height;
  size_hints->max_width = self->window_width;;
  size_hints->max_height = self->window_height;

  XSelectInput(self->display, self->window, ExposureMask|KeyPressMask|ButtonPressMask|ButtonReleaseMask);

  /* disable resize window */

  XSetWMNormalHints(self->display, self->window, size_hints);

  XMapWindow(self->display, self->window);


  /* create / make red color */
  XColor color;
  XParseColor(self->display, self->colormap, "#FF0000", &color);
  XAllocColor(self->display, self->colormap, &color);
  XSetForeground(self->display, self->gc, color.pixel);

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
      XDrawLine(self->display, self->window, self->gc, 10, 200, 390, 200);
    }

    if (self->xevent.type == ButtonPress) {

      if (self->xevent.xbutton.button == 1) {
        printf("LEFT BUTTON PRESSED\n");
      }

    }

    if (self->xevent.type == ButtonRelease) {

      if (self->xevent.xbutton.button == 1) {
        printf("LEFT BUTTON RELEASED\n");
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
