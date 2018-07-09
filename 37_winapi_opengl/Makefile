CC = i686-w64-mingw32-gcc

LIBS += -mwindows 
LIBS += -lopengl32

all: 37_winapi_opengl.exe

37_winapi_opengl.exe: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	wine 37_winapi_opengl.exe 

file:
	file 37_winapi_opengl.exe

clean:
	rm -f 37_winapi_opengl.exe *.o
