#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string.h>

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
unsigned int red_pixel;
unsigned int blue_pixel;
XSizeHints* size_hints;
GC gc;

XColor red_color;
XColor blue_color;
Colormap colormap;

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

  colormap = DefaultColormap(display, 0);

  XParseColor(display, colormap, "#FF0000", &red_color);
  XAllocColor(display, colormap, &red_color);
  red_pixel = red_color.pixel;

  XParseColor(display, colormap, "#0000FF", &blue_color);
  XAllocColor(display, colormap, &blue_color);
  blue_pixel = blue_color.pixel;

  gc = DefaultGC(display, screen_num);

  window = XCreateSimpleWindow(display, root_window, 0, 0, window_width, window_height, 0, black_pixel, white_pixel);

  XSelectInput(display, window, ExposureMask|KeyPressMask|PointerMotionMask|ButtonPressMask|ButtonReleaseMask);

  size_hints = XAllocSizeHints();

  size_hints->flags = PMinSize|PMaxSize;
  size_hints->min_width = window_width;
  size_hints->min_height = window_height;
  size_hints->max_width = window_width;
  size_hints->max_height = window_height;
  XSetWMNormalHints(display, window, size_hints);

  /* load / set up font */
  const char* fontname = "-*-helvetica-*-r-*-*-14-*-*-*-*-*-*-*";
  XFontStruct* font = XLoadQueryFont(display, fontname);
  if (!font) {
    printf("ERROR: 'Unable to load font %s.'.\n", fontname);
    return -1;
  }

  XSetFont(display, gc, font->fid);

  XMapWindow(display, window);

  while (is_open) {

    XNextEvent(display, &xevent);

    if (xevent.type == Expose) {

      /* center the text in the middle of the window */
      int direction;
      int ascent;
      int descent;
      XCharStruct overall;

      const char* text = "Tom Stormland";
      int text_len = strlen(text);
      XTextExtents(font, text, text_len, &direction, &ascent, &descent, &overall);

      int x = (window_width - overall.width) / 2;
      int y = window_height / 2 + (ascent - descent) / 2;

      XDrawString(display, window, gc, x, y, text, text_len);
    }

    if (xevent.type == KeyPress) {
      if (xevent.xkey.keycode == 9) {
        is_open = 0;
      }
    }

    if (xevent.type == ButtonPress) {

    }

    if (xevent.type == ButtonRelease) {
    }

    if (xevent.type == MotionNotify) {

    }

  }

  XDestroyWindow(display, window);
  XCloseDisplay(display);

  return 0;
}
