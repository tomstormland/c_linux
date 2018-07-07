CC = gcc
LIBS += -lX11

all: 18_buffer

18_buffer: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	./18_buffer

clean:
	rm -f *.o 18_buffer
