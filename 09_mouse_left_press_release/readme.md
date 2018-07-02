09_mouse_left_press_release
===========================

```c

XSelectInput(display, window, ExposureMask|KeyPressMask|ButtonPressMask|ButtonReleaseMask);

if (xevent.type == ButtonPress) {

  if (xevent.xbutton.button == 1) {
    /* left button pressed */
  }

}

if (xevent.type == ButtonRelease) {

  if (xevent.xbutton.button == 1) {
    /* left button released */
  }

}
```
