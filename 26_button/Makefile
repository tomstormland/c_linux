CC = gcc

LIBS += -lX11

all: 26_button

26_button: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	./26_button

clean:
	rm -f 26_button
