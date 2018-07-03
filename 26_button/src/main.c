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
unsigned int red_pixel;
unsigned int blue_pixel;
XSizeHints* size_hints;
GC gc;

XColor red_color;
XColor blue_color;
Colormap colormap;

int buttonX;
int buttonY;
int buttonWidth = 80;
int buttonHeight = 30;

int mouseX = 0;
int mouseY = 0;

int intersection = 0;

void x_button_draw(unsigned int color_pixel) {

  XSetForeground(display, gc, color_pixel);

  XDrawRectangle(display, window, gc, buttonX, buttonY, buttonWidth, buttonHeight);
}

int main(int argc, char *argv[]) {

  buttonX = window_width / 2 - buttonWidth / 2;
  buttonY = window_height / 2 - buttonHeight / 2;

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

  XMapWindow(display, window);

  while (is_open) {

    XNextEvent(display, &xevent);

    if (xevent.type == Expose) {
      x_button_draw(black_pixel);
    }

    if (xevent.type == KeyPress) {
      if (xevent.xkey.keycode == 9) {
        is_open = 0;
      }
    }

    if (xevent.type == ButtonPress) {
      if (intersection) {
        /* button pressed */
        x_button_draw(blue_pixel);
        printf("BUTTON PRESSED\n");
      }
    }

    if (xevent.type == ButtonRelease) {
        x_button_draw(black_pixel);
    }

    if (xevent.type == MotionNotify) {
      mouseX = xevent.xmotion.x;
      mouseY = xevent.xmotion.y;

      if (mouseX > buttonX && mouseX < buttonX + buttonWidth && mouseY > buttonY && mouseY < buttonY + buttonHeight) {
        if (intersection == 0) {
          intersection = 1;
          /* enter button */
          x_button_draw(red_pixel);
        }
      } else if (intersection == 1) {
        intersection = 0;
        /* mouse leave */
        x_button_draw(black_pixel);
      }
    }

  }

  XDestroyWindow(display, window);
  XCloseDisplay(display);

  return 0;
}
