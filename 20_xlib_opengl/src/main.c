#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

int visual_attribute_list[] = {
  GLX_RGBA,
  GLX_DEPTH_SIZE,
  24,
  GLX_DOUBLEBUFFER,
  None
};

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
  XSetWindowAttributes window_attributes;
  Colormap colormap;
  GLXContext gl_context;
  XVisualInfo* visual_info;
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

  /* choose visual info */
  self->visual_info = glXChooseVisual(self->display, 0, visual_attribute_list);

  /* create colormap */
  self->colormap = XCreateColormap(self->display, self->root_window, self->visual_info->visual, AllocNone);

  if (self->visual_info == NULL) {
    printf("ERROR: 'No appropriate visual found.'.\n");
    return -1;
  }

  /* set up window */
  self->window_x = 0;
  self->window_y = 0;
  self->window_width = 400;
  self->window_height = 400;
  self->window_border_width = 2;

  /* set up window attributes */
  self->window_attributes.colormap = self->colormap;
  self->window_attributes.event_mask = ExposureMask|KeyPressMask;

  /* set up size hints */
  self->size_hints = XAllocSizeHints();
  self->size_hints->flags = PMinSize|PMaxSize;
  self->size_hints->min_width = self->window_width;
  self->size_hints->min_height = self->window_width;
  self->size_hints->max_width = self->window_width;
  self->size_hints->max_height = self->window_width;

  self->window = XCreateWindow(self->display, self->root_window, self->window_x, self->window_y, self->window_width, self->window_height, self->window_border_width, self->visual_info->depth, InputOutput, self->visual_info->visual, CWColormap|CWEventMask, &self->window_attributes);

  XSetWMNormalHints(self->display, self->window, self->size_hints);

  XSelectInput(self->display, self->window, ExposureMask|KeyPressMask|ButtonPressMask|ButtonReleaseMask);

  XMapWindow(self->display, self->window);

  /* create opengl context */
  self->gl_context = glXCreateContext(self->display, self->visual_info, NULL, GL_TRUE);

  /* enable / set current opengl context */
  glXMakeCurrent(self->display, self->window, self->gl_context);

  /* enable extensions */
  glEnable(GL_DEPTH_TEST);

  /* create / set up graphic contexts */
  self->gc = XCreateGC(self->display, self->window, 0, NULL);

  XSetForeground(self->display, self->gc, self->window_border);

  return 0;
}

int interface_destroy(struct Interface *self) {

  glXMakeCurrent(self->display, None, NULL);
  glXDestroyContext(self->display, self->gl_context);
  XDestroyWindow(self->display, self->window);
  XCloseDisplay(self->display);

  return 0;
}

int interface_main_loop(struct Interface *self) {

  while (self->open) {
    XNextEvent(self->display, &self->xevent);

    if (self->xevent.type == Expose) {

      glViewport(0, 0, self->window_width, self->window_height);

      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 20.0f);

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

      glBegin(GL_QUADS);
      glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-0.75f, -0.75f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(+0.75f, -0.75f, 0.0f);
      glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(+0.75f, +0.75f, 0.0f);
      glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(-0.75f, +0.75f, 0.0f);
      glEnd();

      glXSwapBuffers(self->display, self->window);

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
