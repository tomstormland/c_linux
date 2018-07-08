CC = gcc

CFLAGS += -I ../common/include
CFLAGS += -I include/

LIBS += -ldl
LIBS += -lX11
LIBS += -lGL
LIBS += -lm

all: 57_xlib_motion

57_xlib_motion: m-circle.o main.o ../common/glad.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: src/main.c
	$(CC) $(CFLAGS) -o $@ -c $^

m-circle.o: src/m-circle.c
	$(CC) $(CFLAGS) -o $@ -c $^

run:
	./57_xlib_motion

clean:
	rm -f 57_xlib_motion *.o
