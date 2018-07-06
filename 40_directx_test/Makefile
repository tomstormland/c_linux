CC = i686-w64-mingw32-g++

LIBS += -mwindows 
LIBS += -ld3d9

all: 40_directx_test

40_directx_test: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	wine 40_directx_test.exe 

file:
	file 40_directx_test.exe

clean:
	rm -f 40_directx_test.exe *.o
