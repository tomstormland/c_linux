CC = gcc

CFLAGS += -I GL/include

LIBS += -ldl
LIBS += -lX11
LIBS += -lGL

all: 56_xlib_random_lines

56_xlib_random_lines: glad.o main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: src/main.c
	$(CC) $(CFLAGS) -o $@ -c $^

glad.o: GL/src/glad.c
	$(CC) $(CFLAGS) -o $@ -c $^ 

clean:
	rm -f *.o 56_xlib_random_lines

run:
	./56_xlib_random_lines
