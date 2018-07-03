CC = gcc

CFLAGS += -I GL/include

LIBS += -ldl
LIBS += -lX11
LIBS += -lGL

all: 31_opengl_rectangle

31_opengl_rectangle: glad.o main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: src/main.c
	$(CC) $(CFLAGS) -o $@ -c $^

glad.o: GL/src/glad.c
	$(CC) $(CFLAGS) -o $@ -c $^ 

run:
	./31_opengl_rectangle

clean:
	rm -f *.o 31_opengl_rectangle
