CC = i686-w64-mingw32-gcc

WINDRES = i686-w64-mingw32-windres

CFLAGS += -mwindows
CFLAGS += -I include/

all: winapi_014_animation_one.exe

winapi_014_animation_one.exe: resource.o main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: src/main.c
	$(CC) $(CFLAGS) -o $@ -c $^

resource.o: resource.rc
	$(WINDRES) $^ $@

run:
	./winapi_014_animation_one.exe

clean:
	rm -f winapi_014_animation_one.exe *.o
