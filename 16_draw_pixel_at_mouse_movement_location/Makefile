CC = gcc
LIBS += -lX11

all: 16_draw_pixel_at_mouse_movement_location

16_draw_pixel_at_mouse_movement_location: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	./16_draw_pixel_at_mouse_movement_location

clean:
	rm -f 16_draw_pixel_at_mouse_movement_location *.o
