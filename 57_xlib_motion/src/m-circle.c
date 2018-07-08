#include <m-circle.h>
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <math.h>
#include <default.h>
#include <linmath.h>

mat4x4 model_matrix;

MCircle *MCircleCreate(float x, float y, int sectors) 
{
  MCircle *circle = malloc(sizeof(MCircle));

  circle->sectors = sectors;

  circle->x = x;
  circle->y = y;

  glGenVertexArrays(1, &circle->vao);
  glGenBuffers(1, &circle->vbo);

  float vertices[circle->sectors][3];

  int i;

  for (i=0; i<circle->sectors; i++) {
    float angle = 2 * M_PI * i / circle->sectors;

    float x = cosf(angle);
    float y = sinf(angle);

    vertices[i][0] = x;
    vertices[i][1] = y;
    vertices[i][2] = 0.0f;
  }

  glBindVertexArray(circle->vao);
  glBindBuffer(GL_ARRAY_BUFFER, circle->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glBindVertexArray(circle->vao);
  glBindVertexArray(0);

  return circle;
}

int MCircleDraw(MCircle *circle) 
{
  glBindVertexArray(circle->vao);
  mat4x4_identity(model_matrix);
  mat4x4_translate(model_matrix, circle->x, circle->y, 0.0f);
  glUniformMatrix4fv(interface->model_u_loc, 1, GL_FALSE, (const float *)model_matrix);
  glDrawArrays(GL_TRIANGLE_FAN, 0, circle->sectors);
  glBindVertexArray(0);
  return 0;
}
