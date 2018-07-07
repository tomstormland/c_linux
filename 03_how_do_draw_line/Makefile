CC = gcc

LIBS += -lX11

all: 03_how_do_draw_line

03_how_do_draw_line: src/main.c
	$(CC) -o $@ $^ $(LIBS)

clean:
	rm -f 03_how_do_draw_line *.o
