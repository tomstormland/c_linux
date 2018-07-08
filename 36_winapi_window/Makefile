.PHONY: test
UNAME := $(shell uname)

CC = i686-w64-mingw32-gcc

ifeq ($(UNAME), MINGW32_NT-6.1)
	CC = i686-w64-mingw32-gcc
else
	CC = i686-w64-mingw32-gcc
endif

LIBS += -municode
LIBS += -mwindows 

all: test 36_winapi_window

test:
	# OP: $(UNAME)

36_winapi_window: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
ifeq ($(UNAME), MINGW32_NT-6.1)
	./36_winapi_window.exe
else
	wine 36_winapi_window.exe
endif

file:
	file 36_winapi_window.exe

clean:
	rm -f *.o 36_winapi_window
