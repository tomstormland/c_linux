
CC = gcc
LIBS += -lX11

all: 14_draw_rectangle_center_window_filled

14_draw_rectangle_center_window_filled: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	./14_draw_rectangle_center_window_filled

clean:
	rm -f 14_draw_rectangle_center_window_filled *.o
