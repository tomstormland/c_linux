#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>

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

  self->window = XCreateSimpleWindow(self->display, self->root_window, self->window_x, self->window_y, self->window_border_width, self->window_width, self->window_height, self->window_border, self->window_background);

  XSelectInput(self->display, self->window, ExposureMask|KeyPressMask|ButtonPressMask|ButtonReleaseMask);

  XMapWindow(self->display, self->window);

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
