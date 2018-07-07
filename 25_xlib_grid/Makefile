CC = gcc

LIBS += -lX11

all: 25_xlib_grid

25_xlib_grid: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	./25_xlib_grid

clean:
	rm -f *.o 25_xlib_grid
