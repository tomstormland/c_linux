.PHONY: test

UNAME := $(shell uname)

CC = i686-w64-mingw32-gcc

LIBS += -municode
LIBS += -mwindows 
LIBS += -lopengl32

all: test winapi_012_opengl_animation.exe


test:
	# OP: $(UNAME)

winapi_012_opengl_animation.exe: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
ifeq ($(UNAME), MINGW32_NT-6.1)
	./winapi_012_opengl_animation.exe
else
	wine winapi_012_opengl_animation.exe
endif

file:
	file winapi_012_opengl_animation.exe

clean:
	rm -f *.o winapi_012_opengl_animation
