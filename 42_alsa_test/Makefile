CC = gcc

LIBS = $(shell pkg-config --libs alsa)
CFLAGS = $(shell pkg-config --cflags alsa)

all: 42_alsa_test

42_alsa_test: src/main.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

run: 
	./42_alsa_test

clean:
	rm -f 42_alsa_test *.o
