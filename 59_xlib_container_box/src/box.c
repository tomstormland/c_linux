#include <stdlib.h>
#include <string.h>
#include <box.h>

M_Box* M_MakeBox(const char *text) {

  M_Box* box = malloc(sizeof(M_Box));

  box->text = malloc(sizeof(char) * strlen(text) + 1);

  strcpy(box->text, text);

  return box;
}
