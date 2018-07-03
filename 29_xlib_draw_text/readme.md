29_xlib_draw_text
=================

```c
...

/* load / set up font */
const char* fontname = "-*-helvetica-*-r-*-*-14-*-*-*-*-*-*-*";
XFontStruct* font = XLoadQueryFont(display, fontname);
if (!font) {
  printf("ERROR: 'Unable to load font %s.'.\n", fontname);
  return -1;
}

XSetFont(display, gc, font->fid);

...

if (xevent.type == Expose) {

  /* center the text in the middle of the window */
  int direction;
  int ascent;
  int descent;
  XCharStruct overall;

  const char* text = "Tom Stormland";
  int text_len = strlen(text);
  XTextExtents(font, text, text_len, &direction, &ascent, &descent, &overall);

  int x = (window_width - overall.width) / 2;
  int y = window_height / 2 + (ascent - descent) / 2;

  XDrawString(display, window, gc, x, y, text, text_len);
}

...
```
