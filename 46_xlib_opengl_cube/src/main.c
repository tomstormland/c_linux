#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <glad/glad.h>
#include <GL/glx.h>
#include <linmath.h>
#include <time.h>
#include <math.h>

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
int shader_program;
unsigned int vao, vbo;

clock_t start_time;
clock_t current_time;

mat4x4 model_matrix;
mat4x4 view_matrix;
mat4x4 projection_matrix;

unsigned int model_uniform_location;
unsigned int view_uniform_location;
unsigned int projection_uniform_location;

int main(int argc, char *argv[]) {

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
  window_attributes.event_mask = ExposureMask|KeyPressMask|StructureNotifyMask;

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

  /* create / set up shader program */
  FILE* file;
  int success;
  char info_log[512];
  long bufsize;
  size_t new_len;

  /* create vertex shader */
  char* vertex_shader_source = NULL;
  file = fopen("default.vs", "r");
  if (file == NULL) {
    printf("ERROR: 'Failed to open default.vs.'\n");
    return -1;
  }
  if (fseek(file, 0L, SEEK_END) != 0) {
    printf("ERROR: 'Failed to seek file end default.vs.'\n");
    return -1;
  }
  bufsize = ftell(file);
  if (bufsize == -1) {
    printf("ERROR: 'Unable to read buf size.'.\n");
    return -1;
  }
  vertex_shader_source = malloc(sizeof(char) * (bufsize + 1));
  if (fseek(file, 0L, SEEK_SET) != 0) {
    printf("ERROR: 'Failed to seek file set.'.\n");
    return -1;
  }
  new_len = fread(vertex_shader_source, sizeof(char), bufsize, file);
  if (ferror(file) != 0) {
    printf("ERROR: 'Unable to read file.'\n");
    return -1;
  }
  vertex_shader_source[new_len++] = '\0';
  fclose(file);

  int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, (const char**)&vertex_shader_source, NULL);
  glCompileShader(vertex_shader);

  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
    printf("ERROR: 'Failed to compile vertex shader: %s'.\n", info_log);
    return -1;
  }

  /* create fragment shader */
  char* fragment_shader_source = NULL;
  file = fopen("default.fs", "r");
  if (file == NULL) {
    printf("ERROR: 'Failed to open default.fs.'\n");
    return -1;
  }
  if (fseek(file, 0L, SEEK_END) != 0) {
    printf("ERROR: 'Failed to seek file end default.fs.'\n");
    return -1;
  }
  bufsize = ftell(file);
  if (bufsize == -1) {
    printf("ERROR: 'Unable to read buf size.'.\n");
    return -1;
  }
  fragment_shader_source = malloc(sizeof(char) * (bufsize + 1));
  if (fseek(file, 0L, SEEK_SET) != 0) {
    printf("ERROR: 'Failed to seek file set.'.\n");
    return -1;
  }
  new_len = fread(fragment_shader_source, sizeof(char), bufsize, file);
  if (ferror(file) != 0) {
    printf("ERROR: 'Unable to read file.'\n");
    return -1;
  }
  fragment_shader_source[new_len++] = '\0';
  fclose(file);

  int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, (const char**)&fragment_shader_source, NULL);
  glCompileShader(fragment_shader);

  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
    printf("ERROR: 'Failed to compile fragment shader: %s'.\n", info_log);
    return -1;
  }

  /* create / link shader program */
  shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader_program, 512, NULL, info_log);
    printf("ERROR: 'Failed to link shader program: %s.'\n", info_log);
    return -1;
  }

  free(vertex_shader_source);
  free(fragment_shader_source);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  /* create vertex array object and vertex buffer object */
  float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.3f, 1.0f, 1.0f,
    +0.5f, -0.5f, -0.5f,  0.3f, 1.0f, 1.0f,
    +0.5f, +0.5f, -0.5f,  0.3f, 1.0f, 1.0f,
    +0.5f, +0.5f, -0.5f,  0.3f, 1.0f, 1.0f,
    -0.5f, +0.5f, -0.5f,  0.3f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.3f, 1.0f, 1.0f,

    -0.5f, -0.5f, +0.5f,  1.0f, 1.0f, 0.3f,
    +0.5f, -0.5f, +0.5f,  1.0f, 1.0f, 0.3f,
    +0.5f, +0.5f, +0.5f,  1.0f, 1.0f, 0.3f,
    +0.5f, +0.5f, +0.5f,  1.0f, 1.0f, 0.3f,
    -0.5f, +0.5f, +0.5f,  1.0f, 1.0f, 0.3f,
    -0.5f, -0.5f, +0.5f,  1.0f, 1.0f, 0.3f,

    -0.5f, +0.5f, +0.5f,  1.0f, 0.3f, 0.3f,
    -0.5f, +0.5f, -0.5f,  1.0f, 0.3f, 0.3f,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.3f, 0.3f,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.3f, 0.3f,
    -0.5f, -0.5f, +0.5f,  1.0f, 0.3f, 0.3f,
    -0.5f, +0.5f, +0.5f,  1.0f, 0.3f, 0.3f,

    +0.5f, +0.5f, +0.5f,  0.3f, 0.3f, 1.0f,
    +0.5f, +0.5f, -0.5f,  0.3f, 0.3f, 1.0f,
    +0.5f, -0.5f, -0.5f,  0.3f, 0.3f, 1.0f,
    +0.5f, -0.5f, -0.5f,  0.3f, 0.3f, 1.0f,
    +0.5f, -0.5f, +0.5f,  0.3f, 0.3f, 1.0f,
    +0.5f, +0.5f, +0.5f,  0.3f, 0.3f, 1.0f,

    -0.5f, -0.5f, -0.5f,  0.3f, 1.0f, 0.3f,
    +0.5f, -0.5f, -0.5f,  0.3f, 1.0f, 0.3f,
    +0.5f, -0.5f, +0.5f,  0.3f, 1.0f, 0.3f,
    +0.5f, -0.5f, +0.5f,  0.3f, 1.0f, 0.3f,
    -0.5f, -0.5f, +0.5f,  0.3f, 1.0f, 0.3f,
    -0.5f, -0.5f, -0.5f,  0.3f, 1.0f, 0.3f,

    -0.5f, +0.5f, -0.5f,  0.3f, 0.3f, 0.3f,
    +0.5f, +0.5f, -0.5f,  0.3f, 0.3f, 0.3f,
    +0.5f, +0.5f, +0.5f,  0.3f, 0.3f, 0.3f,
    +0.5f, +0.5f, +0.5f,  0.3f, 0.3f, 0.3f,
    -0.5f, +0.5f, +0.5f,  0.3f, 0.3f, 0.3f,
    -0.5f, +0.5f, -0.5f,  0.3f, 0.3f, 0.3f,
  };

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  /* enable OpenGL extensions  */
  glEnable(GL_DEPTH_TEST);

  start_time = clock();
  current_time = clock();

  /* load identity matrixes */
  mat4x4_identity(model_matrix);
  mat4x4_identity(view_matrix);
  mat4x4_identity(projection_matrix);

  /* use the created shader program */
  glUseProgram(shader_program);

  /* set up matrix uniform locations */
  model_uniform_location = glGetUniformLocation(shader_program, "model");
  view_uniform_location = glGetUniformLocation(shader_program, "view");
  projection_uniform_location = glGetUniformLocation(shader_program, "projection");

  /* set up projection matrix */
  mat4x4_perspective(projection_matrix, 45.0f * M_PI / 180, (float)window_width/(float)window_height, 0.1f, 100.0f);

  /* set up view matrix */
  mat4x4_translate(view_matrix, 0.0f, 0.0f, -3.0f);

  while (is_open) {

    clock_t difference = current_time - start_time;

    /*printf("%d\n", difference);*/

    int msec = difference;
    float sec = (float)msec / 1000000.0;

    while (XPending(display)) {
      XNextEvent(display, &xevent);

      if (xevent.type == Expose) {
        glViewport(0, 0, window_width, window_height);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
      }

      if (xevent.type == KeyPress) {
        if (xevent.xkey.keycode == 9) {
          is_open = 0;
        }
      }

      if (xevent.type == ConfigureNotify) {
        if (xevent.xconfigure.width != window_width) {
          window_width = xevent.xconfigure.width;
        }
        if (xevent.xconfigure.height != window_height) {
          window_height = xevent.xconfigure.height;
        }
        glViewport(0, 0, window_width, window_height);
      }
    }

    /* clear the screen / context */
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(vao);

    /* load identity matrix to model matrix */
    mat4x4_identity(model_matrix);

    /* update model / cube rotation */
    mat4x4_rotate(model_matrix, model_matrix, 0.5f, -0.8f, -0.2f, (float)sec);

    /* update matrices */
    glUniformMatrix4fv(model_uniform_location, 1, GL_FALSE, (const float*)model_matrix);
    glUniformMatrix4fv(view_uniform_location, 1, GL_FALSE, (const float*)view_matrix);
    glUniformMatrix4fv(projection_uniform_location, 1, GL_FALSE, (const float*)projection_matrix);

    /* draw the triangles / cube */
    glDrawArrays(GL_TRIANGLES, 0, 36);

    /* swap the front / back buffers */
    glXSwapBuffers(display, window);

    /* update current time */
    current_time = clock();
  }

  /* destroy, clean up, and exit */
  glXMakeCurrent(display, None, NULL);
  glXDestroyContext(display, gl_context);
  XDestroyWindow(display, window);
  XCloseDisplay(display);

  return 0;
}
