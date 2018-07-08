58_xlib_mouse_wheel
=====================

```c

XSelectInput(..., ..., ButtonPressMask);

while ...

  /* mouse wheel handle */
  if (xevent.xbutton.button == 4) {
    /* scrolling up */
  } else if (xevent.xbutton.button == 5) {
    /* scrolling down */
  }

```
