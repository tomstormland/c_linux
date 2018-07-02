12_draw_circle_center_window
==============================

```c
int x = 200, y = 200;
unsigned int w = 100, h = 100;

x = x - w / 2;
y = y - h / 2;

int a1 = 0, a2 = 360*64;

XDrawArc(self->display, self->window, self->gc, x, y, w, h, a1, a2);
```
