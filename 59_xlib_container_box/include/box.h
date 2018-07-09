#ifndef MY_BOX_H
#define MY_BOX_H

struct _M_Box {
  char *text;
};

typedef struct _M_Box M_Box;

M_Box* M_MakeBox(const char *text);

#endif
