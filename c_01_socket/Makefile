CC = gcc

all: c_01_socket_server c_01_socket_client

c_01_socket_server: src/server/main.c
	$(CC) -o $@ $^

c_01_socket_client: src/client/main.c
	$(CC) -o $@ $^

run:
	./c_01_socket_server 

clean:
	rm -f *.o c_01_socket_server c_01_socket_client
