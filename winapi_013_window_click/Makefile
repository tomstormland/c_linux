CC = i686-w64-mingw32-gcc

CFLAGS += -mwindows

all: winapi_013_window_click.exe

winapi_013_window_click.exe: main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: src/main.c
	$(CC) $(CFLAGS) -o $@ -c $^

run:
	./winapi_013_window_click.exe

clean:
	rm -f winapi_013_window_click.exe *.o
