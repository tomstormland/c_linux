
CC = gcc
LIBS += -lX11

all: 10_draw_red_line

10_draw_red_line: src/main.c
	$(CC) -o $@ $^ $(LIBS)

clean:
	rm -f *.o 10_draw_red_line
