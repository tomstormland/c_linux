CC = gcc
LIBS += -lX11

all: 19_image

19_image: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	./19_image

clean:
	rm -f *.o 19_image
