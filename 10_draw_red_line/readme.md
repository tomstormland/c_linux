10_draw_red_line
=================

```c
XColor color;
Colormap colormap;
GC gc;

gc = XCreateGC(self->display, self->window, 0, NULL);
colormap = DefaultColormap(display, 0);

XParseColor(display, colormap, "#FF0000", &color);
XAllocColor(display, colormap, &color);

XSetForeground(display, gc, color.pixel);

XDrawLine(display, window, gc, 10, 200, 390, 200);
```
