13_draw_rectangle_center_window
===============================

```c
int x = 200;
int y = 200;

int w = 100;
int h = 100;

x = x - w / 2;
y = y - h / 2;

XDrawRectangle(self->display, self->window, self->gc, x, y, w, h);
```
