17_window_enter_background_red_leave_blue
=========================================

```c
GC gc;
Colormap colormap;
XColor color_red;
XColor color_blue;

XSelectInput(display, window, EnterWindowMask|LeaveWindowMask);

/* create / set up graphic contexts */
gc = XCreateGC(display, window, 0, NULL);

/* create / set up colormap */
colormap = DefaultColormap(display, 0);

/* set up read and blue colors */
XParseColor(display, colormap, "#FF3333", &color_red);
XAllocColor(display, colormap, &color_red);

XParseColor(display, colormap, "#3333FF", &color_blue);
XAllocColor(display, colormap, &color_blue);

if (xevent.type == EnterNotify) {
  XSetForeground(display, gc, color_red.pixel);
  XFillRectangle(display, window, gc, 0, 0, window_width, window_height);
}

if (xevent.type == LeaveNotify) {
  XSetForeground(display, gc, color_blue.pixel);
  XFillRectangle(display, window, gc, 0, 0, window_width, window_height);
}
```
