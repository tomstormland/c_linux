.PHONY: test

UNAME := $(shell uname)

CC = i686-w64-mingw32-gcc

LIBS += -municode
LIBS += -mwindows 

all: test winapi_001_window


test:
	# OP: $(UNAME)

winapi_001_window: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
ifeq ($(UNAME), MINGW32_NT-6.1)
	./winapi_001_window.exe
else
	wine winapi_001_window.exe
endif

file:
	file winapi_001_window.exe

clean:
	rm -f *.o winapi_001_window
