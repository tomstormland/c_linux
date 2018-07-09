CC = gcc

all: socket_01_get_ip_str

socket_01_get_ip_str: src/main.c
	$(CC) -o $@ $^

run:
	./socket_01_get_ip_str

clean:
	rm -f *.o socket_01_get_ip_str
