CC = gcc
LIBS += -lX11

all: 11_draw_pixel_center_window

11_draw_pixel_center_window: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	./11_draw_pixel_center_window

clean:
	rm -f 11_draw_pixel_center_window *.o
