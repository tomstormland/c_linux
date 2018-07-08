.PHONY: test

UNAME := $(shell uname)

CC = i686-w64-mingw32-gcc

CFLAGS += -municode
CFLAGS += -mwindows 

all: test winapi_009_mouse_click.exe

test:
	# OP: $(UNAME)

winapi_009_mouse_click.exe: main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: src/main.c
	$(CC) $(CFLAGS) -o $@ -c $^

run:
ifeq ($(UNAME), MINGW32_NT-6.1)
	./winapi_009_mouse_click.exe
else
	wine winapi_009_mouse_click.exe
endif

clean:
	rm -f *.o winapi_009_mouse_click.exe
