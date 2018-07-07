CC = gcc

LIBS += -lX11

all: 04_disable_resize_window

04_disable_resize_window: src/main.c
	$(CC) -o $@ $^ $(LIBS)

clean:
	rm -f 04_disable_resize_window *.o
