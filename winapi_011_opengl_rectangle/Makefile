.PHONY: test

UNAME := $(shell uname)

CC = i686-w64-mingw32-gcc

LIBS += -municode
LIBS += -mwindows 
LIBS += -lopengl32

all: test winapi_011_opengl_rectangle.exe


test:
	# OP: $(UNAME)

winapi_011_opengl_rectangle.exe: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
ifeq ($(UNAME), MINGW32_NT-6.1)
	./winapi_011_opengl_rectangle.exe
else
	wine winapi_011_opengl_rectangle.exe
endif

file:
	file winapi_011_opengl_rectangle.exe

clean:
	rm -f *.o winapi_011_opengl_rectangle
