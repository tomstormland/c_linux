#ifndef M_CIRCLE_H
#define M_CIRCLE_H

struct _MCircle {
  int vao, vbo;
  float x;
  float y;
  int sectors;
};

typedef struct _MCircle MCircle;

MCircle *MCircleCreate(float x, float y, int sectors);
int MCircleDraw(MCircle *circle);

#endif
