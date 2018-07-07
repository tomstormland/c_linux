CC = gcc
LIBS += -lX11

all: 15_draw_pixel_at_mouse_press_location

15_draw_pixel_at_mouse_press_location: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	./15_draw_pixel_at_mouse_press_location

clean:
	rm -f 15_draw_pixel_at_mouse_press_location *.o
