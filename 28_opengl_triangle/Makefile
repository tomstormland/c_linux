CC = gcc

CFLAGS += -I GL/include

LIBS += -ldl
LIBS += -lX11
LIBS += -lGL

all: 28_opengl_triangle

28_opengl_triangle: glad.o main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: src/main.c
	$(CC) $(CFLAGS) -o $@ -c $^

glad.o: GL/src/glad.c
	$(CC) $(CFLAGS) -o $@ -c $^ 

run:
	./28_opengl_triangle

clean:
	rm -f *.o 28_opengl_triangle
