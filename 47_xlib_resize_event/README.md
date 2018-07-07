47_xlib_resize_event
=====================

```c
int main(int argc, char *argv[]) {

  ...

  XSelectInput(display, window, ExposureMask|KeyPressMask|StructureNotifyMask);

  ... while

  if (xevent.xconfigure.width != window_width || xevent.xconfigure.height != window_height) {
    window_width = xevent.xconfigure.width;
    window_height = xevent.xconfigure.height;
  }

  ...

}
```
