CC = gcc

OBJ += main.o

LIBS += -lX11

all: 58_xlib_mouse_wheel

58_xlib_mouse_wheel: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: src/main.c
	$(CC) $(CFLAGS) -o $@ -c $^

run:
	./58_xlib_mouse_wheel

clean:
	rm -f *.o 58_xlib_mouse_wheel
