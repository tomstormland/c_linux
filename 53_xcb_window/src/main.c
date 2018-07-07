#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <xcb/xcb.h>
#include <xcb/xcb_icccm.h>

int main(int argc, char *argv[]) {

  xcb_connection_t* connection;
  xcb_screen_t* screen;
  xcb_drawable_t window;
  xcb_gcontext_t foreground;
  xcb_gcontext_t background;
  xcb_generic_event_t* event;
  xcb_size_hints_t size_hints;

  uint32_t mask = 0;
  uint32_t values[2];

  char string[] = "LOREM TEXT";
  uint8_t string_len = strlen(string);

  xcb_rectangle_t rectangles[] = {
    {40, 40, 20, 20}
  };

  connection = xcb_connect(NULL, NULL);

  /* get the first screen */
  screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;

  /* root window */
  window = screen->root;

  /* create black (foreground) graphic context */
  foreground = xcb_generate_id(connection);
  mask = XCB_GC_FOREGROUND|XCB_GC_GRAPHICS_EXPOSURES;
  values[0] = screen->black_pixel;
  values[1] = 0;
  xcb_create_gc(connection, foreground, window, mask, values);

  /* create white (background) graphic context */
  background = xcb_generate_id(connection);
  mask = XCB_GC_BACKGROUND|XCB_GC_GRAPHICS_EXPOSURES;
  values[0] = screen->white_pixel;
  values[1] = 0;
  xcb_create_gc(connection, background, window, mask, values);

  /* create the window */
  window = xcb_generate_id(connection);
  mask = XCB_CW_BACK_PIXEL|XCB_CW_EVENT_MASK;
  values[0] = screen->white_pixel;
  values[1] = XCB_EVENT_MASK_EXPOSURE|XCB_EVENT_MASK_KEY_PRESS;
  xcb_create_window(connection, XCB_COPY_FROM_PARENT, window, screen->root, 0, 0, 400, 400, 1, XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual, mask, values);

  /* set / update size hints */
  xcb_icccm_size_hints_set_min_size(&size_hints, 400, 400);
  xcb_icccm_size_hints_set_max_size(&size_hints, 400, 400);

  xcb_icccm_set_wm_size_hints(connection, window, XCB_ATOM_WM_NORMAL_HINTS, &size_hints);

  /* map the window on the screen */
  xcb_map_window(connection, window);

  xcb_flush(connection);

  while ( (event = xcb_wait_for_event(connection)) ) {
    switch (event->response_type & ~0x8) {
      case XCB_EXPOSE:
        {
          xcb_poly_rectangle(connection, window, foreground, 1, rectangles);
          xcb_image_text_8(connection, string_len, window, background, 20, 20, string);
          xcb_flush(connection);
        } break;
      case XCB_KEY_PRESS:
        {
          goto endloop;
        } break;
    }
  }

endloop:

  return 0;
}
