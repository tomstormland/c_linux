.PHONY: test

UNAME := $(shell uname)

CC = i686-w64-mingw32-gcc

CFLAGS += -municode
CFLAGS += -mwindows 

all: test winapi_007_center_window.exe

test:
	# OP: $(UNAME)

winapi_007_center_window.exe: main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: src/main.c
	$(CC) $(CFLAGS) -o $@ -c $^

run:
ifeq ($(UNAME), MINGW32_NT-6.1)
	./winapi_007_center_window.exe
else
	wine winapi_007_center_window.exe
endif

clean:
	rm -f *.o winapi_007_center_window.exe
