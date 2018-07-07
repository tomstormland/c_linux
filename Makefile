all:
	$(MAKE) -C 00_test_window
	$(MAKE) -C 01_xlib_window
	$(MAKE) -C 02_close_window_escape_key
	$(MAKE) -C 03_how_do_draw_line
	$(MAKE) -C 04_disable_resize_window
	$(MAKE) -C 05_move_window_center_screen
	$(MAKE) -C 06_draw_text
	$(MAKE) -C 07_mouse_left_click
	$(MAKE) -C 08_change_window_background
	$(MAKE) -C 09_mouse_left_press_release
	$(MAKE) -C 10_draw_red_line
	$(MAKE) -C 11_draw_pixel_center_window
	$(MAKE) -C 12_draw_circle_center_window
	$(MAKE) -C 13_draw_rectangle_center_window
	$(MAKE) -C 14_draw_rectangle_center_window_filled
	$(MAKE) -C 15_draw_pixel_at_mouse_press_location
	$(MAKE) -C 16_draw_pixel_at_mouse_movement_location
	$(MAKE) -C 17_window_enter_background_red_leave_blue
	$(MAKE) -C 18_buffer
	$(MAKE) -C 19_image
	$(MAKE) -C 20_xlib_opengl
	$(MAKE) -C 21_xlib_unblock_next_event
	$(MAKE) -C 22_unblocking_socket
	$(MAKE) -C 23_half_a_pyramid
	$(MAKE) -C 24_pyramid
	$(MAKE) -C 25_xlib_grid
	$(MAKE) -C 26_button
	$(MAKE) -C 27_glad_test
	$(MAKE) -C 28_opengl_triangle
	$(MAKE) -C 29_xlib_draw_text
	$(MAKE) -C 30_pipe_and_fork
	$(MAKE) -C 31_opengl_rectangle
	$(MAKE) -C 32_opengl_texture
	$(MAKE) -C 33_opengl_rotation
	$(MAKE) -C 34_opengl_cube
	$(MAKE) -C 35_xlib_child_window
	$(MAKE) -C 36_winapi_window
	$(MAKE) -C 37_winapi_opengl
	$(MAKE) -C 38_time
	$(MAKE) -C 39_conio_graphics
	$(MAKE) -C 40_directx_test
	$(MAKE) -C 41_random_number
	$(MAKE) -C 42_alsa_test
	$(MAKE) -C 43_alsa_test_2
	$(MAKE) -C 44_alsa_sound_playback
	$(MAKE) -C 45_alsa_sound_playback_2
	$(MAKE) -C 46_xlib_opengl_cube
	$(MAKE) -C 47_xlib_resize_event
	$(MAKE) -C 48_xlib_opengl_text_render
	$(MAKE) -C 49_xlib_opengl_frames_per_second
	$(MAKE) -C 50_read_dir
	$(MAKE) -C 51_fork_test
	$(MAKE) -C 52_xlib_grid_2

clean:
	$(MAKE) -C 00_test_window clean
	$(MAKE) -C 01_xlib_window clean
	$(MAKE) -C 02_close_window_escape_key clean
	$(MAKE) -C 03_how_do_draw_line clean
	$(MAKE) -C 04_disable_resize_window clean
	$(MAKE) -C 05_move_window_center_screen clean
	$(MAKE) -C 06_draw_text clean
	$(MAKE) -C 07_mouse_left_click clean
	$(MAKE) -C 08_change_window_background clean
	$(MAKE) -C 09_mouse_left_press_release clean
	$(MAKE) -C 10_draw_red_line clean
	$(MAKE) -C 11_draw_pixel_center_window clean
	$(MAKE) -C 12_draw_circle_center_window clean
	$(MAKE) -C 13_draw_rectangle_center_window clean
	$(MAKE) -C 14_draw_rectangle_center_window_filled clean
	$(MAKE) -C 15_draw_pixel_at_mouse_press_location clean
	$(MAKE) -C 16_draw_pixel_at_mouse_movement_location clean
	$(MAKE) -C 17_window_enter_background_red_leave_blue clean
	$(MAKE) -C 18_buffer clean
	$(MAKE) -C 19_image clean
	$(MAKE) -C 20_xlib_opengl clean
	$(MAKE) -C 21_xlib_unblock_next_event clean
	$(MAKE) -C 22_unblocking_socket clean
	$(MAKE) -C 23_half_a_pyramid clean
	$(MAKE) -C 24_pyramid clean
	$(MAKE) -C 25_xlib_grid clean
	$(MAKE) -C 26_button clean
	$(MAKE) -C 27_glad_test clean
	$(MAKE) -C 28_opengl_triangle clean
	$(MAKE) -C 29_xlib_draw_text clean
	$(MAKE) -C 30_pipe_and_fork clean
	$(MAKE) -C 31_opengl_rectangle clean
	$(MAKE) -C 32_opengl_texture clean
	$(MAKE) -C 33_opengl_rotation clean
	$(MAKE) -C 34_opengl_cube clean
	$(MAKE) -C 35_xlib_child_window clean
	$(MAKE) -C 36_winapi_window clean
	$(MAKE) -C 37_winapi_opengl clean
	$(MAKE) -C 38_time clean
	$(MAKE) -C 39_conio_graphics clean
	$(MAKE) -C 40_directx_test clean
	$(MAKE) -C 41_random_number clean
	$(MAKE) -C 42_alsa_test clean
	$(MAKE) -C 43_alsa_test_2 clean
	$(MAKE) -C 44_alsa_sound_playback clean
	$(MAKE) -C 45_alsa_sound_playback_2 clean
	$(MAKE) -C 46_xlib_opengl_cube clean
	$(MAKE) -C 47_xlib_resize_event clean
	$(MAKE) -C 48_xlib_opengl_text_render clean
	$(MAKE) -C 49_xlib_opengl_frames_per_second clean
	$(MAKE) -C 50_read_dir clean
	$(MAKE) -C 51_fork_test clean
	$(MAKE) -C 52_xlib_grid_2 clean
