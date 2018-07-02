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
  unsigned int window_border_pixel;
  unsigned int window_background_pixel;
  unsigned int window_border_width;
  int window_depth;
  unsigned int window_class;
  Visual* window_visual;
  unsigned long window_valuemask;
  XSetWindowAttributes window_attributes;
  Window window;
  Window root_window;
  XEvent xevent;
  Display *display;
  int screen_num;
  GC gc;
  Colormap colormap;
  XColor color_red;
  XColor color_blue;
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
  self->window_border_pixel = BlackPixel(self->display, self->screen_num);
  self->window_background_pixel = WhitePixel(self->display, self->screen_num);
  self->window_x = 0;
  self->window_y = 0;
  self->window_width = 400;
  self->window_height = 400;
  self->window_border_width = 2;

  self->window_depth = CopyFromParent;
  self->window_class = InputOutput;
  self->window_valuemask = CWBackPixel|CWBorderPixel;
  self->window_visual = XDefaultVisual(self->display, self->screen_num);
  self->window_attributes.background_pixel = self->window_background_pixel;
  self->window_attributes.border_pixel = self->window_border_pixel;


  self->window = XCreateWindow(self->display, self->root_window, self->window_x, self->window_y, self->window_width, self->window_height, self->window_border_width, self->window_depth, self->window_class, self->window_visual, self->window_valuemask, &self->window_attributes);

  /* set up size hints */
  self->size_hints = XAllocSizeHints();
  self->size_hints->flags = PMinSize|PMaxSize;
  self->size_hints->min_width = self->window_width;
  self->size_hints->min_height = self->window_width;
  self->size_hints->max_width = self->window_width;
  self->size_hints->max_height = self->window_width;

  XSetWMNormalHints(self->display, self->window, self->size_hints);

  XSelectInput(self->display, self->window, ExposureMask|KeyPressMask|ButtonPressMask|ButtonReleaseMask|EnterWindowMask|LeaveWindowMask);

  XMapWindow(self->display, self->window);

  /* create / set up graphic contexts */
  self->gc = XCreateGC(self->display, self->window, 0, NULL);

  /* create / set up colormap */
  self->colormap = DefaultColormap(self->display, 0);

  /* set up read and blue colors */
  XParseColor(self->display, self->colormap, "#FF3333", &self->color_red);
  XAllocColor(self->display, self->colormap, &self->color_red);

  XParseColor(self->display, self->colormap, "#3333FF", &self->color_blue);
  XAllocColor(self->display, self->colormap, &self->color_blue);

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

    if (self->xevent.type == EnterNotify) {
      XSetForeground(self->display, self->gc, self->color_red.pixel);
      XFillRectangle(self->display, self->window, self->gc, 0, 0, self->window_width, self->window_height);
    }

    if (self->xevent.type == LeaveNotify) {
      XSetForeground(self->display, self->gc, self->color_blue.pixel);
      XFillRectangle(self->display, self->window, self->gc, 0, 0, self->window_width, self->window_height);
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
