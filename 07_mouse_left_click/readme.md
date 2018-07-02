07_mouse_left_click
===================

```c
XSelectInput(display, window, ButtonPressMask);

typedef struct {
  int type; /* ButtonPress or ButtonReleast */
  unsigned int state;
  unsigned int button;
} XButtonEvent;

typedef union _XEvent {
  int type;
  XButtonEvent xbutton;
} XEvent;

if (xevent.type == ButtonPress) {

  if (xevent.xbutton.button == 1) {
    printf("LEFT BUTTON PRESSED\n");
  }

}
```
