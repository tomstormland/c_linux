02_close_window_escape_key
==========================

close window with escape key
----------------------------

```c
/* how do I do that, hmm */

typedef struct {
  ...
  unsigned int keycode;
  ...
} XKeyEvent;

typedef union _XEvent {
  ...
  XKeyEvent xkey;
  ...
} XEvent;

/* what is escape keycode, .. it is 9 */

/* int main() ... */

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
