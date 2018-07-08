CC = gcc

CFLAGS += -I include/

all: glad.o

glad.o: src/glad.c
	$(CC) $(CFLAGS) -o $@ -c $^
