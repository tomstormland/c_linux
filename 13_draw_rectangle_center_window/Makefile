CC = gcc
LIBS += -lX11

all: 13_draw_rectangle_center_window

13_draw_rectangle_center_window: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run: 
	./13_draw_rectangle_center_window

clean:
	rm -f 13_draw_rectangle_center_window *.o
