08_change_window_background
===========================

```c
XColor color;
Colormap colormap;
char red[] = "#FF3333";
unsigned long background;

background = WhitePixel(display, screen);
colormap = DefaultColormap(display, 0);
XParseColor(display, colormap, red, &color);
XAllocColor(display, colormap, &color);

background = color.pixel;

window = XCreateSimpleWindow(display, root_window, 10, 10, 200, 200, 1, border, background);
```
