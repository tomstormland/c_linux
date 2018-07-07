CC = gcc

CFLAGS += -I GL/include
CFLAGS += -I include

CFLAGS += $(shell pkg-config --cflags freetype2)

LIBS += -ldl
LIBS += -lX11
LIBS += -lGL
LIBS += -lm

LIBS += $(shell pkg-config --libs freetype2)

all: 48_xlib_opengl_text_render

48_xlib_opengl_text_render: glad.o main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: src/main.c
	$(CC) $(CFLAGS) -o $@ -c $^

glad.o: GL/src/glad.c
	$(CC) $(CFLAGS) -o $@ -c $^ 

run:
	./48_xlib_opengl_text_render

clean:
	rm -f *.o 48_xlib_opengl_text_render
