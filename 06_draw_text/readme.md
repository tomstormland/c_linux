06_draw_text
==============

```c
...

if (xevent.type == Expose) {
  char * text = "Tom Stormland";
  XDrawString(display, window, gc, 10, 20, text, strlen(text));
}

...
```
