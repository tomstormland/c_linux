CC = gcc
LIBS += -lX11

all: 21_xlib_unblock_next_event

21_xlib_unblock_next_event: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	./21_xlib_unblock_next_event

clean:
	rm -f 21_xlib_unblock_next_event *.o
