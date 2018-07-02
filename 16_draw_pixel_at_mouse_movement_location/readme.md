16_draw_pixel_at_mouse_movement_location
=========================================

```c
XSelectInput(display, window, PointerMotionMask);

if (xevent.type == MotionNotify) {
  int x = xevent.xmotion.x;
  int y = xevent.xmotion.y;
  XDrawPoint(display, window, gc, x, y);
}

```
