CC = gcc

CFLAGS += -I GL/include

LIBS += -ldl
LIBS += -lX11
LIBS += -lGL

all: 27_glad_test

27_glad_test: glad.o main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: src/main.c
	$(CC) $(CFLAGS) -o $@ -c $^

glad.o: GL/src/glad.c
	$(CC) $(CFLAGS) -o $@ -c $^ 

run:
	./27_glad_test
