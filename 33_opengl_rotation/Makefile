CC = gcc

CFLAGS += -I GL/include
CFLAGS += -I include

LIBS += -ldl
LIBS += -lX11
LIBS += -lGL
LIBS += -lm

all: 33_opengl_rotation

33_opengl_rotation: glad.o stb_image.o main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: src/main.c
	$(CC) $(CFLAGS) -o $@ -c $^

glad.o: GL/src/glad.c
	$(CC) $(CFLAGS) -o $@ -c $^ 

stb_image.o: src/stb_image.c
	$(CC) $(CFLAGS) -o $@ -c $^

run:
	./33_opengl_rotation

clean:
	rm -f *.o 33_opengl_rotation
