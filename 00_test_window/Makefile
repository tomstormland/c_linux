CC = gcc
LIBS += -lX11

all: 00_test_window

00_test_window: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	./00_test_window

clean:
	rm -f 00_test_window *.o
