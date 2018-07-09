CC = gcc

CFLAGS += -I include

LIBS += -lX11

OBJ += main.o
OBJ += window.o
OBJ += container.o
OBJ += box.o

all: 59_xlib_container_box

59_xlib_container_box: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: src/main.c
	$(CC) $(CFLAGS) -o $@ -c $^

window.o: src/window.c
	$(CC) $(CFLAGS) -o $@ -c $^

container.o: src/container.c
	$(CC) $(CFLAGS) -o $@ -c $^

box.o: src/box.c
	$(CC) $(CFLAGS) -o $@ -c $^

run: 
	./59_xlib_container_box

clean:
	rm -f *.o 59_xlib_container_box
