#include <window.h>
#include <stdio.h>
#include <stdlib.h>

M_Window *window;

int M_WindowInitialize(unsigned int width, unsigned int height) {

  XSizeHints *size_hints;

  window = malloc(sizeof(M_Window));

  window->open = 1;

  window->width = width;
  window->height = height;

  unsigned long black_pixel;
  unsigned long white_pixel;

  window->display = XOpenDisplay(NULL);

  if (window->display == NULL) {
    fprintf(stderr, "ERROR: Was unable to open display.\n");
    return -1;
  }

  window->screen_num = DefaultScreen(window->display);

  window->gc = DefaultGC(window->display, window->screen_num);

  black_pixel = BlackPixel(window->display, window->screen_num);
  white_pixel = WhitePixel(window->display, window->screen_num);

  window->root = RootWindow(window->display, window->screen_num);

  size_hints = XAllocSizeHints();
  size_hints->flags = PMinSize|PMaxSize;
  size_hints->min_width = window->width;
  size_hints->min_height = window->height;
  size_hints->max_width = window->width;
  size_hints->max_height = window->height;

  window->handle = XCreateSimpleWindow(window->display, window->root, 0, 0, window->width, window->height, 1, black_pixel, white_pixel);

  XSetWMNormalHints(window->display, window->handle, size_hints);

  XSelectInput(window->display, window->handle, ExposureMask|KeyPressMask|ButtonPressMask);

  XMapWindow(window->display, window->handle);

  return 0;
}
