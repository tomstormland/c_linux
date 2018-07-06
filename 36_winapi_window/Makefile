CC = i686-w64-mingw32-gcc

LIBS += -mwindows -municode

all: 36_winapi_window

36_winapi_window: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	wine 36_winapi_window.exe

file:
	file 36_winapi_window.exe
