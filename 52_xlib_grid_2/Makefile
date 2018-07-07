LIBS += -lX11

all: 52_xlib_grid_2

52_xlib_grid_2: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	./52_xlib_grid_2

clean:
	rm -f 52_xlib_grid_2 *.o
