CC = gcc

LIBS += -lX11

all: 25_xlib_brid

25_xlib_brid: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	./25_xlib_brid
