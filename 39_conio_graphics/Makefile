CC = i686-w64-mingw32-gcc

all: 39_conio_graphics

39_conio_graphics: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	wine 39_conio_graphics.exe 

file:
	file 39_conio_graphics.exe

clean:
	rm -f 39_conio_graphics.exe *.o
