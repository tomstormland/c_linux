04_disable_resize_window
==========================

```c
/* set min and max same as width */

#include <X11/Xutil.h>

XSizeHints *size_hints = XAllocSizeHints();
size_hints->flags = PMinSize|PMaxSize;
size_hints->min_width = 200;
size_hints->min_height = 200;
size_hints->max_width = 200;
size_hints->max_height = 200;
XSetWMNormalHints(display, window, size_hints);
```
