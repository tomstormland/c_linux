CC = gcc

LIBS += -lX11

all: 47_xlib_resize_event 

47_xlib_resize_event: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	./47_xlib_resize_event

clean:
	rm -f *.o 47_xlib_resize_event
