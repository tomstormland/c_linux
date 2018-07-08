#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* fontname = "fixed";
XFontStruct* font;
Display *display;
Window window;
XEvent xevent;
int screen;
Window root_window;
unsigned long border;
unsigned long background;
XSizeHints *size_hints;
GC gc;

struct _MInterface {
  unsigned int width;
  unsigned int height;
};

typedef struct _MInterface MInterface;

MInterface *interface;

struct _MCard {
  unsigned int id;
  int x;
  int y;
  unsigned int width;
  unsigned int height;
  char text[256];
};

typedef struct _MCard MCard;

MCard cards[100];

int MInitializeCards() {
  int i;

  for (i=0; i<100; i++) {
    MCard *card = &cards[i];

    card->id = i;

    card->x = 50;
    card->y = 10 + 30 * i + 10 * i;
    card->width = interface->width - 20 - 40;
    card->height = 30;

    memset(card->text, '\0', sizeof(card->text));

    if (i == 0) {
      sprintf(card->text, "XLib Window Test");
    } else if (i == 1) {
      sprintf(card->text, "XLib Window");
    } else if (i == 2) {
      sprintf(card->text, "XLib Escape Close Window");
    } else if (i == 3) {
      sprintf(card->text, "XLib Draw Line");
    } else if (i == 4) {
      sprintf(card->text, "XLib Disable Window Resizing");
    } else if (i == 5) {
      sprintf(card->text, "XLib Move Window Center Screen");
    } else if (i == 6) {
      sprintf(card->text, "XLib Draw Text");
    }
  }

  return 0;
}

int MCardDraw(MCard* card) {

  int text_len;
  char text[256] = {'\0'};
  int x, y;
  int direction;
  int ascent;
  int descent;
  XCharStruct overall;

  /* draw the main rectangle */
  XDrawRectangle(display, window, gc, card->x, card->y, card->width, card->height);

  /* draw the rectangle text */
  sprintf(text, "%s", card->text);
  text_len = strlen(text);

  XTextExtents(font, text, text_len, &direction, &ascent, &descent, &overall);

  x = card->x + 10;
  y = card->y + 30 / 2 + (ascent - descent) / 2;

  XDrawString(display, window, gc, x, y, text, text_len);

  /* draw the number box */
  XDrawRectangle(display, window, gc, 10, card->y, 30, 30);

  /* draw the number */
  sprintf(text, "%d", card->id);
  text_len = strlen(text);

  XTextExtents(font, text, text_len, &direction, &ascent, &descent, &overall);

  x = 10 + (30 - overall.width) / 2;
  y = card->y + 30 / 2 + (ascent - descent) / 2;

  XDrawString(display, window, gc, x, y, text, text_len);

  return 0;
}

int main(int argc, char *argv[])
{

  interface = malloc(sizeof(MInterface));

  interface->width = 700;
  interface->height = 800;

  display = XOpenDisplay(NULL);

  if (display == NULL) {
    fprintf(stderr, "ERROR: 'Unable to open display.'.");
    return -1;
  }

  screen = DefaultScreen(display);

  root_window = RootWindow(display, screen);

  border = BlackPixel(display, screen);
  background = WhitePixel(display, screen);

  size_hints = XAllocSizeHints();
  size_hints->flags = PMinSize|PMaxSize;
  size_hints->min_width = interface->width;
  size_hints->min_height = interface->height;
  size_hints->max_width = interface->width;
  size_hints->max_height = interface->height;

  window = XCreateSimpleWindow(display, root_window, 0, 0, interface->width, interface->height, 1, border, background);

  XSetWMNormalHints(display, window, size_hints);

  XSelectInput(display, window, ExposureMask|KeyPressMask);

  gc = DefaultGC(display, screen);

  font = XLoadQueryFont(display, fontname);
  if (!font) {
    printf("ERROR: Was unable to load font.\n");
    return -1;
  }

  XSetFont(display, gc, font->fid);

  XMapWindow(display, window);

  MInitializeCards();

  while (1) 
  {
    XNextEvent(display, &xevent);

    if (xevent.type == Expose) {
      int i;

      for (i=0; i<100; i++) {
        MCardDraw(&cards[i]);
      }
    }

    if (xevent.type == KeyPress) {
      if (xevent.xkey.keycode == 9) {
        break;
      }
    }

  }

  XCloseDisplay(display);

  return 0;
}
