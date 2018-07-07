CC = gcc

LIBS += -lX11

all: 02_close_window_escape_key

02_close_window_escape_key: src/main.c
	$(CC) -o $@ $^ $(LIBS)

clean:
	rm -f 02_close_window_escape_key *.o
