CC = gcc
LIBS += -lX11
LIBS += -lGL
LIBS += -lGLU

all: 20_xlib_opengl

20_xlib_opengl: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	./20_xlib_opengl

clean:
	rm -f *.o 20_xlib_opengl
