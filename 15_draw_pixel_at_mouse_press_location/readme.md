14_draw_rectangle_center_window_filled
======================================

```c
if (xevent.type == ButtonPress) {

  if (xevent.xbutton.button == 1) {
    int x = xevent.xbutton.x;
    int y = xevent.xbutton.y;
    XDrawPoint(display, window, gc, x, y);
  }

}
```
