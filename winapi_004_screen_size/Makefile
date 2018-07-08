.PHONY: test

UNAME := $(shell uname)

CC = i686-w64-mingw32-gcc

LIBS += -municode
LIBS += -mwindows 

all: test winapi_004_screen_size

test:
	# OP: $(UNAME)

winapi_004_screen_size: main.o
	$(CC) -o $@ $^ $(LIBS)

main.o: src/main.c
	$(CC) -o $@ -c $^

run:
ifeq ($(UNAME), MINGW32_NT-6.1)
	./winapi_004_screen_size
else
	wine winapi_004_screen_size.exe
endif

file:
	file winapi_004_screen_size.exe

clean:
	rm -f *.o winapi_004_screen_size
