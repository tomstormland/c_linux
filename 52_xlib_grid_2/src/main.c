#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string.h>

int is_open = 1;

unsigned int window_width = 400;
unsigned int window_height = 400;

int mouseX;
int mouseY;

XEvent xevent;
Display* display;
int screen_num;
Window window;
Window root_window;
unsigned int white_pixel;
unsigned int black_pixel;
unsigned int red_pixel;
unsigned int blue_pixel;
unsigned int green_pixel;
XSizeHints* size_hints;
GC gc;
XFontStruct* font;

GC red_pen;
GC black_pen;
GC blue_pen;
GC green_pen;

XColor red_color;
XColor black_color;
XColor blue_color;
XColor green_color;
Colormap colormap;

struct Button {
  int x;
  int y;
  int width;
  int height;
  int mouseover;
  char text[512];
  int button_1_down;
};

struct Button buttons[36];

int DrawButton(struct Button *button, GC gc) {

  XClearArea(display, window, button->x, button->y, button->width, button->height, 0);

  XDrawRectangle(display, window, gc, button->x, button->y, button->width, button->height);

  /* center the text in the middle of the window */
  int direction;
  int ascent;
  int descent;
  XCharStruct overall;

  char * text = button->text;
  int text_len = strlen(text);
  XTextExtents(font, text, text_len, &direction, &ascent, &descent, &overall);

  int i, j;
  int x = button->x + (button->width - overall.width) / 2;
  int y = button->y + button->height / 2 + (ascent - descent) / 2;

  XDrawString(display, window, gc, x, y, text, text_len);
}

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

  XParseColor(display, colormap, "#000000", &black_color);
  XAllocColor(display, colormap, &black_color);

  XParseColor(display, colormap, "#0000FF", &blue_color);
  XAllocColor(display, colormap, &blue_color);
  blue_pixel = blue_color.pixel;

  XParseColor(display, colormap, "#00FF00", &green_color);
  XAllocColor(display, colormap, &green_color);
  green_pixel = green_color.pixel;

  gc = DefaultGC(display, screen_num);

  window = XCreateSimpleWindow(display, root_window, 0, 0, window_width, window_height, 0, black_pixel, white_pixel);

  /* create red pen */
  red_pen = XCreateGC(display, window, 0, NULL);
  XSetForeground(display, red_pen, red_pixel);

  /* create blue pen */
  blue_pen = XCreateGC(display, window, 0, NULL);
  XSetForeground(display, blue_pen, blue_pixel);

  /* create green pen */
  green_pen = XCreateGC(display, window, 0, NULL);
  XSetForeground(display, green_pen, green_pixel);

  /* create black pen */
  black_pen = XCreateGC(display, window, 0, NULL);
  XSetForeground(display, black_pen, black_color.pixel);

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
  font = XLoadQueryFont(display, fontname);
  if (!font) {
    printf("ERROR: 'Unable to load font %s.'.\n", fontname);
    return -1;
  }

  XSetFont(display, gc, font->fid);

  /* initialize buttons */
  int i, j, index = 0;
  for (i=0; i<6; i++) {
    for (j=0; j<6; j++) {
      float x = 30 + 40 * i + 20 * i;
      float y = 30 + 40 * j + 20 * j;
      buttons[index].x = x;
      buttons[index].y = y;
      buttons[index].width = 40;
      buttons[index].height = 40;

      buttons[index].mouseover = 0;
      buttons[index].button_1_down = 0;

      sprintf(buttons[index].text, "%d", index);

      /*float x = 30 + i + i*(40+2);*/
      /*XDrawRectangle(display, window, red_pen, x, y, 40, 40);*/

      index += 1;
    }
  }

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
      /*XTextExtents(font, text, text_len, &direction, &ascent, &descent, &overall);*/

      int i, j;
      int x = (window_width - overall.width) / 2;
      int y = window_height / 2 + (ascent - descent) / 2;

      XDrawString(display, window, gc, x, y, text, text_len);
      /* draw all buttons */
      for (i=0; i<36; i++) {
        DrawButton(&buttons[i], black_pen);
        /*XDrawRectangle(display, window, gc, buttons[i].x, buttons[i].y, buttons[i].width, buttons[i].height);*/
      }
      /*for (i=0; i<6; i++) {*/
      /*for (j=0; j<6; j++) {*/
      /*float x = 30 + 40 * i + 20 * i;*/
      /*float y = 30 + 40 * j + 20 * j;*/
      /*[>float x = 30 + i + i*(40+2);<]*/
      /*XDrawRectangle(display, window, red_pen, x, y, 40, 40);*/
      /*}*/
      /*}*/
    }

    if (xevent.type == KeyPress) {
      if (xevent.xkey.keycode == 9) {
        is_open = 0;
      }
    }

    if (xevent.type == ButtonPress) {

      if (xevent.xbutton.button == 1) {
        for (i=0; i<36; i++) {
          struct Button *button = &buttons[i];
          if (button->mouseover) {
            button->button_1_down = 1;
            /*printf("BUTTON PRESSED [%s].\n", button->text);*/
          }
        }
      }

    }

    if (xevent.type == ButtonRelease) {
      for (i=0; i<36; i++) {
        struct Button *button = &buttons[i];
        if (button->button_1_down && button->mouseover) {
          /*printf("BUTTON RELEASED [%s].\n", button->text);*/
          button->button_1_down = 0;

          if (i == 0) {
            system("../00_test_window/00_test_window");
          } 

          if (i == 1) {
            system("../01_xlib_window/01_xlib_window");
          } 

          if (i == 2) {
            system("../02_close_window_escape_key/02_close_window_escape_key");
          } 

          if (i == 3) {
            system("../03_how_do_draw_line/03_how_do_draw_line");
          } 

          if (i == 4) {
            system("../04_disable_resize_window/04_disable_resize_window");
          } 

          if (i == 5) {
            system("../05_move_window_center_screen/05_move_window_center_screen");
          } 

          if (i == 6) {
            system("../06_draw_text/06_draw_text");
          } 

          if (i == 7) {
            system("../07_mouse_left_click/07_mouse_left_click");
          } 

          if (i == 8) {
            system("../08_change_window_background/08_change_window_background");
          } 

          if (i == 9) {
            system("../09_mouse_left_press_release/09_mouse_left_press_release");
          } 

          if (i == 10) {
            system("../10_draw_red_line/10_draw_red_line");
          } 

          if (i == 11) {
            system("../11_draw_pixel_center_window/11_draw_pixel_center_window");
          } 

          if (i == 12) {
            system("../12_draw_circle_center_window/12_draw_circle_center_window");
          } 

          if (i == 13) {
            system("../13_draw_rectangle_center_window/13_draw_rectangle_center_window");
          } 

          if (i == 14) {
            system("../14_draw_rectangle_center_window_filled/14_draw_rectangle_center_window_filled");
          } 

          if (i == 15) {
            system("../15_draw_pixel_at_mouse_press_location/15_draw_pixel_at_mouse_press_location");
          } 

          if (i == 16) {
            system("../16_draw_pixel_at_mouse_movement_location/16_draw_pixel_at_mouse_movement_location");
          } 

          if (i == 17) {
            system("../17_window_enter_background_red_leave_blue/17_window_enter_background_red_leave_blue");
          } 

          if (i == 18) {
            system("../18_buffer/18_buffer");
          } 

          if (i == 19) {
            system("../19_image/19_image");
          } 

          if (i == 20) {
            system("../20_xlib_opengl/20_xlib_opengl");
          } 

          if (i == 21) {
            system("../21_xlib_unblock_next_event/21_xlib_unblock_next_event");
          } 

          if (i == 22) {

          } 

          if (i == 23) {
            system("../23_half_a_pyramid/23_half_a_pyramid");
          } 

          if (i == 24) {
            system("../24_pyramid/24_pyramid");
          } 

          if (i == 25) {
            system("../25_xlib_grid/25_xlib_grid");
          } 

          if (i == 26) {
            system("../26_button/26_button");
          } 

          if (i == 27) {
            system("../27_glad_test/27_glad_test");
          } 

          if (i == 28) {
            system("(cd ../28_opengl_triangle; ./28_opengl_triangle)");
          } 

          if (i == 29) {
            system("(cd ../29_xlib_draw_text; ./29_xlib_draw_text)");
          } 

          if (i == 30) {
            system("(cd ../30_pipe_and_fork; ./30_pipe_and_fork)");
          } 

          if (i == 31) {
            system("(cd ../31_opengl_rectangle; ./31_opengl_rectangle)");
          } 

          if (i == 32) {
            system("(cd ../32_opengl_texture; ./32_opengl_texture)");
          } 

          if (i == 33) {
            system("(cd ../33_opengl_rotation; ./33_opengl_rotation)");
          } 

          if (i == 34) {
            system("(cd ../34_opengl_cube; ./34_opengl_cube)");
          } 

          if (i == 35) {
            system("(cd ../35_xlib_child_window; ./35_xlib_child_window)");
          } 
        }
      }
    }

    if (xevent.type == MotionNotify) {
      int i;

      mouseX = xevent.xmotion.x;
      mouseY = xevent.xmotion.y;

      /* check cursor / button collisions */
      for (i=0; i<36; i++) {
        struct Button *button = &buttons[i];
        if (mouseX > button->x && mouseX < button->x + button->width && mouseY > button->y && mouseY < button->y + button->height) {
          if (!button->mouseover) {

            /* mouse entered button */
            DrawButton(button, red_pen);

            button->mouseover = 1;
          }
        } else {

          if (button->mouseover) {

            /* mouse left button */
            DrawButton(button, black_pen);

            button->mouseover = 0;
          }
        }
      }

    }

  }

  XDestroyWindow(display, window);
  XCloseDisplay(display);

  return 0;
}
