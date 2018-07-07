CC = gcc
LIBS += -lX11

all: 12_draw_circle_center_window

12_draw_circle_center_window: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	./12_draw_circle_center_window

clean:
	rm -f *.o 12_draw_circle_center_window
