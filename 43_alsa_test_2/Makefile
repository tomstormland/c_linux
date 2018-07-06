CC = gcc

LIBS = $(shell pkg-config --libs alsa)
CFLAGS = $(shell pkg-config --cflags alsa)

all: 43_alsa_test_2

43_alsa_test_2: src/main.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

run: 
	./43_alsa_test_2

clean:
	rm -f 43_alsa_test_2 *.o
