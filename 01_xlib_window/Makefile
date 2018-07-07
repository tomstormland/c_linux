CC = gcc
LIBS = -lX11
CFLAGS = 

all: 01_xlib_window

01_xlib_window: src/main.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f 01_xlib_window *.o
