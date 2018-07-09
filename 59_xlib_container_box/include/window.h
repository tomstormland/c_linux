#ifndef MY_WINDOW_H
#define MY_WINDOW_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>

struct _M_Window {
  XEvent event;
  int open;
  Window handle;
  Window root;
  Display *display;
  unsigned int width;
  unsigned int height;
  int screen_num;
  GC gc;
};

typedef struct _M_Window M_Window;

int M_WindowInitialize(unsigned int width, unsigned int height);

extern M_Window *window;

#endif
