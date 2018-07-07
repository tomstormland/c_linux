#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <glad/glad.h>
#include <GL/glx.h>
#include <linmath.h>
#include <time.h>
#include <math.h>
#include <ft2build.h>
#include FT_FREETYPE_H  

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

mat4x4 text_projection_matrix;

unsigned int model_uniform_location;
unsigned int view_uniform_location;
unsigned int projection_uniform_location;

/* freetype / front / variables  */

int text_shader_program;
unsigned int text_vao;
unsigned int text_vbo;

FT_Library ft;
FT_Face face;

struct Char {
  unsigned int texture;
  float size[2];
  float bearing[2];
  unsigned int advance;
};

struct Char characters[128];

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

  FILE* file;
  int success;
  char info_log[512];
  long bufsize;
  size_t new_len;
  int shader;
  char *source = NULL;

  /* A01: create / set up shader program */
  shader_program = glCreateProgram();

  /* A02: create vertex shader */
  file = fopen("default.vs", "r");
  if (file == NULL) {
    printf("ERROR: 'Failed to open default.vs.'\n");
    return -1;
  }
  fseek(file, 0L, SEEK_END);
  bufsize = ftell(file);
  source = malloc(sizeof(char) * (bufsize + 1));
  fseek(file, 0L, SEEK_SET);
  new_len = fread(source, sizeof(char), bufsize, file);
  source[new_len++] = '\0';
  fclose(file);

  shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(shader, 1, (const char**)&source, NULL);
  glCompileShader(shader);
  free(source);

  glAttachShader(shader_program, shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, info_log);
    printf("ERROR: 'Failed to compile vertex shader: %s'.\n", info_log);
    return -1;
  }

  /* A03: create fragment shader */
  file = fopen("default.fs", "r");
  if (file == NULL) {
    printf("ERROR: 'Failed to open default.fs.'\n");
    return -1;
  }
  fseek(file, 0L, SEEK_END);
  bufsize = ftell(file);
  source = malloc(sizeof(char) * (bufsize + 1));
  fseek(file, 0L, SEEK_SET);
  new_len = fread(source, sizeof(char), bufsize, file);
  source[new_len++] = '\0';
  fclose(file);

  shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(shader, 1, (const char**)&source, NULL);
  glCompileShader(shader);
  free(source);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, info_log);
    printf("ERROR: 'Failed to compile fragment shader: %s'.\n", info_log);
    return -1;
  }
  glAttachShader(shader_program, shader);
  glDeleteShader(shader);

  /* A04: create / link shader program */
  glLinkProgram(shader_program);
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader_program, 512, NULL, info_log);
    printf("ERROR: 'Failed to link shader program: %s.'\n", info_log);
    return -1;
  }

  /* M01: create text shader program */
  text_shader_program = glCreateProgram();

  /* A02: create vertex shader */
  file = fopen("text.vs", "r");
  if (file == NULL) {
    printf("ERROR: 'Failed to open text.vs.'\n");
    return -1;
  }
  fseek(file, 0L, SEEK_END);
  bufsize = ftell(file);
  source = malloc(sizeof(char) * (bufsize + 1));
  fseek(file, 0L, SEEK_SET);
  new_len = fread(source, sizeof(char), bufsize, file);
  source[new_len++] = '\0';
  fclose(file);

  shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(shader, 1, (const char**)&source, NULL);
  glCompileShader(shader);
  free(source);

  glAttachShader(text_shader_program, shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, info_log);
    printf("ERROR: 'Failed to compile vertex shader: %s'.\n", info_log);
    return -1;
  }

  /* A03: create fragment shader */
  file = fopen("text.fs", "r");
  if (file == NULL) {
    printf("ERROR: 'Failed to open text.fs.'\n");
    return -1;
  }
  fseek(file, 0L, SEEK_END);
  bufsize = ftell(file);
  source = malloc(sizeof(char) * (bufsize + 1));
  fseek(file, 0L, SEEK_SET);
  new_len = fread(source, sizeof(char), bufsize, file);
  source[new_len++] = '\0';
  fclose(file);

  shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(shader, 1, (const char**)&source, NULL);
  glCompileShader(shader);
  free(source);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, info_log);
    printf("ERROR: 'Failed to compile fragment shader: %s'.\n", info_log);
    return -1;
  }
  glAttachShader(text_shader_program, shader);
  glDeleteShader(shader);

  /* A04: create / link shader program */
  glLinkProgram(text_shader_program);
  glGetProgramiv(text_shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(text_shader_program, 512, NULL, info_log);
    printf("ERROR: 'Failed to link shader program: %s.'\n", info_log);
    return -1;
  }

  /* M02: set up / initialize freetype */
  if (FT_Init_FreeType(&ft)) {
    printf("ERROR: 'Was unable to initialize FreeType Library.'.\n");
    return -1;
  }

  if (FT_New_Face(ft, "Ametic.ttf", 0, &face)) {
    printf("ERROR: 'Was unable to load font.'.\n");
    return -1;
  }

  FT_Set_Pixel_Sizes(face, 0, 48);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  /* M03: load first 128 characters of ASCII set */
  unsigned int i;
  for (i=0; i<128; i++) {

    /* N01: load character. */
    if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
      printf("ERROR: 'Was unable to load glyph.'.\n");
      continue;
    }

    /* N02: generate texture. */
    unsigned int texture;

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    FT_Bitmap *bitmap = &face->glyph->bitmap;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, bitmap->width, bitmap->rows, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap->buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    characters[i].texture = texture;

    characters[i].size[0] = bitmap->width;
    characters[i].size[1] = bitmap->rows;

    characters[i].bearing[0] = face->glyph->bitmap_left;
    characters[i].bearing[1] = face->glyph->bitmap_top;

    characters[i].advance = face->glyph->advance.x;
  }
  glBindTexture(GL_TEXTURE_2D, 0);

  /* M04: destroy freetype once character loading finished */
  FT_Done_Face(face);
  FT_Done_FreeType(ft);

  /* M05: configure text vao / vbo for texture quads */
  glGenVertexArrays(1, &text_vao);
  glGenBuffers(1, &text_vbo);

  glBindVertexArray(text_vao);

  glBindBuffer(GL_ARRAY_BUFFER, text_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

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


  /* update text projection matrix */
  glUseProgram(text_shader_program);

  mat4x4_identity(text_projection_matrix);

  mat4x4_ortho(text_projection_matrix, 0.0f, (float)window_width, 0.0f, (float)window_height, -1.0f, +1.0f);
  glUniformMatrix4fv(glGetUniformLocation(text_shader_program, "projection"), 1, GL_FALSE, (const float *)text_projection_matrix);


  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

    glUseProgram(shader_program);
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

    /* draw text */
    char text[] = "LOREM TEXT";
    float text_x = 30.0f;
    float text_y = 30.0f;
    float text_scale = 1.0f;

    glUseProgram(text_shader_program);

    glEnable(GL_CULL_FACE);

    /* set up color to draw text with */
    glUniform3f(glGetUniformLocation(text_shader_program, "textColor"), 1.0f, 0.0f, 0.0f);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(text_vao);

    /* iterate each character (*ch) in text */
    int i;

    for (i=0; text[i] != '\0'; i++) {
      struct Char* ch = &characters[(int)text[i]];

      float x = text_x + ch->bearing[0] * text_scale;
      float y = text_y - (ch->size[1] - ch->bearing[1]) * text_scale;

      float width = ch->size[0] * text_scale;
      float height = ch->size[1] * text_scale;

      float vertices[6][4] = {
        x,          y + height,  0.0, 0.0,
        x,          y,           0.0, 1.0,
        x + width,  y,           1.0, 1.0,

        x,          y + height,  0.0, 0.0,
        x + width,  y,           1.0, 1.0,
        x + width,  y + height,  1.0, 0.0,
      };

      glBindTexture(GL_TEXTURE_2D, ch->texture);

      glBindBuffer(GL_ARRAY_BUFFER, text_vbo);
      glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
      glBindBuffer(GL_ARRAY_BUFFER, 0);

      glDrawArrays(GL_TRIANGLES, 0, 6);

      text_x += (ch->advance >> 6) * text_scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_CULL_FACE);

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
