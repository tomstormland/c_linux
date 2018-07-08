#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <glad/glad.h>
#include <GL/glx.h>
#include <time.h>

int visual_attribute_list[] = {
  GLX_RGBA,
  GLX_DEPTH_SIZE,
  24,
  GLX_DOUBLEBUFFER,
  None
};

Display* display;
int is_open = 1;
XSizeHints* size_hints;
Window window;
Window root_window;
XVisualInfo* visual_info;
Colormap colormap;
unsigned int window_width = 400;
unsigned int window_height = 400;
XSetWindowAttributes window_attributes;
GLXContext gl_context;
int screen_num;
XEvent xevent;

int main(int argc, char *argv[]) {
  srand(time(NULL));

  /* setup display*/
  display = XOpenDisplay(NULL);

  if (display == NULL) {
    printf("ERROR: 'Unable to open display.'.\n");
    return -1;
  }

  /* set up screen number */
  screen_num = DefaultScreen(display);

  /* set up root window */
  root_window = RootWindow(display, screen_num);

  /* choose visual info */
  visual_info = glXChooseVisual(display, 0, visual_attribute_list);

  if (visual_info == NULL) {
    printf("ERROR: 'No appropriate visual found.'.\n");
    return -1;
  }

  /* set up colormap */
  colormap = XCreateColormap(display, root_window, visual_info->visual, AllocNone);

  /* set up window attributes */
  window_attributes.colormap = colormap;
  window_attributes.event_mask = ExposureMask|KeyPressMask;

  /* set up window hints */
  size_hints = XAllocSizeHints();
  size_hints->flags = PMinSize|PMaxSize;
  size_hints->min_width = window_width;
  size_hints->min_height = window_height;
  size_hints->max_width = window_width;
  size_hints->max_height = window_height;

  /* create the window */
  window = XCreateWindow(display, root_window, 0, 0, window_width, window_height, 0, visual_info->depth, InputOutput, visual_info->visual, CWColormap|CWEventMask, &window_attributes);

  /* load window manager hints */
  XSetWMNormalHints(display, window, size_hints);

  XMapWindow(display, window);

  /* set up the context */
  gl_context = glXCreateContext(display, visual_info, NULL, GL_TRUE);

  /* enable / set current opengl context */
  glXMakeCurrent(display, window, gl_context);

  if (!gladLoadGL()) {
    printf("ERROR: 'Unable to load OpenGL'.\n");
    return -1;
  }

  printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

  /* enable OpenGL extensions  */
  glEnable(GL_DEPTH_TEST);

  while (is_open) {
    XNextEvent(display, &xevent);

    if (xevent.type == Expose) {
      glViewport(0, 0, window_width, window_height);

      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

      glColor3f(1.0f, 0.3f, 0.3f);

      int i;

      struct Line {
        float x1, y1;
        float x2, y2;
      };

      struct Line lines[100];

      for (i=0; i<100; i++) {
        struct Line *line = &lines[i];

        /* random number between -1.0f and +1.0f */
        line->x1 = ((float) (rand() % 200) / 100.0f) - 1.0f;
        line->y1 = ((float) (rand() % 200) / 100.0f) - 1.0f;
        line->x2 = ((float) (rand() % 200) / 100.0f) - 1.0f;
        line->y2 = ((float) (rand() % 200) / 100.0f) - 1.0f;
      }

      glBegin(GL_LINES);
      for (i=0; i<100; i++) {
        struct Line *line = &lines[i];

        glVertex3f(line->x1, line->y1, 0.0f);
        glVertex3f(line->x2, line->y2, 0.0f);
      }
      glEnd();

      glXSwapBuffers(display, window);
    }

    if (xevent.type == KeyPress) {
      if (xevent.xkey.keycode == 9) {
        is_open = 0;
      }
    }
  }

  /* destroy, clean up, and exit */
  glXMakeCurrent(display, None, NULL);
  glXDestroyContext(display, gl_context);
  XDestroyWindow(display, window);
  XCloseDisplay(display);

  return 0;
}
