.PHONY: test

UNAME := $(shell uname)

CC = i686-w64-mingw32-gcc

CFLAGS += -municode
CFLAGS += -mwindows 

all: test winapi_008_mousemove.exe

test:
	# OP: $(UNAME)

winapi_008_mousemove.exe: main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: src/main.c
	$(CC) $(CFLAGS) -o $@ -c $^

run:
ifeq ($(UNAME), MINGW32_NT-6.1)
	./winapi_008_mousemove.exe
else
	wine winapi_008_mousemove.exe
endif

clean:
	rm -f *.o winapi_008_mousemove.exe
