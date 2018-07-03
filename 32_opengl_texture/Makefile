CC = gcc

CFLAGS += -I GL/include
CFLAGS += -I include

LIBS += -ldl
LIBS += -lX11
LIBS += -lGL
LIBS += -lm

all: 32_opengl_texture

32_opengl_texture: glad.o stb_image.o main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: src/main.c
	$(CC) $(CFLAGS) -o $@ -c $^

glad.o: GL/src/glad.c
	$(CC) $(CFLAGS) -o $@ -c $^ 

stb_image.o: src/stb_image.c
	$(CC) $(CFLAGS) -o $@ -c $^

run:
	./32_opengl_texture

clean:
	rm -f *.o 32_opengl_texture
