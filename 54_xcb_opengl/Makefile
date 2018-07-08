CC = gcc

LIBS += -lX11
LIBS += -lxcb
LIBS += -lX11-xcb
LIBS += -lGL

all: 54_xcb_opengl

54_xcb_opengl: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	./54_xcb_opengl

clean:
	rm -f 54_xcb_opengl *.o
