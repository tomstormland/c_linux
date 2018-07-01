02_close_window_escape_key
==========================

close window with escape key
----------------------------

```c
/* how do I do that, hmm */

typedef struct {
  int type;
  int x, y;
  int x_root, y_root;
  unsigned int state;
  unsigned int keycode;
  ...
} XKeyEvent;

typedef union _XEvent {
  int type;
  XAnyEvent xany;
  XKeyEvent xkey;
  ...
} XEvent;

/* what is escape keycode, .. it is 9 */

while (open) 
{
 // ...
  if (xevent.type == KeyPress) {

    if (xevent.xkey.keycode == 9) {
      open = 0;
    }

  }
  // ...
}

```
