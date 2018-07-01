03_how_do_draw_line
===================

```c
/* how do I draw a line */
GC gc = XDefaultGC(display, screen);

...
if (xevent.type == Expose) {
  XDrawLine(display, window, gc, 0, 0, 100, 100);
}
...

```

MORE
===============

```c
XCreateGC(display, drawable, valuemask, values);

/* what is XColor */

XColor xcolor;

xcolor.red = 32000;
xcolor.green = 65000;
xcolor.blue = 32000;
xcolor.flags = DoRed|DoGreen|DoBlue;
XAllocColors(d, cmap, &xcolor);

XAllocNamedColor(display, colormap, "yellow", &yellow, &yellow);

XSetForeground(display, gc, xcolor.pixel);

```
