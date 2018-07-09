CC = gcc

all: server client

server: src/server.c
	$(CC) -o $@ $^

client: src/client.c
	$(CC) -o $@ $^

run:
	./server

clean:
	rm -f server client *.o
