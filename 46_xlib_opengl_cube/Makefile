CC = gcc

CFLAGS += -I GL/include
CFLAGS += -I include

LIBS += -ldl
LIBS += -lX11
LIBS += -lGL
LIBS += -lm

all: 46_xlib_opengl_cube

46_xlib_opengl_cube: glad.o main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: src/main.c
	$(CC) $(CFLAGS) -o $@ -c $^

glad.o: GL/src/glad.c
	$(CC) $(CFLAGS) -o $@ -c $^ 

run:
	./46_xlib_opengl_cube

clean:
	rm -f *.o 46_xlib_opengl_cube
