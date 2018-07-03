CC = gcc

LIBS += -lX11

all: 29_xlib_draw_text

29_xlib_draw_text: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	./29_xlib_draw_text

clean:
	rm -f 29_xlib_draw_text
