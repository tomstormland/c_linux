.PHONY: test

UNAME := $(shell uname)

CC = i686-w64-mingw32-gcc

LIBS += -municode
LIBS += -mwindows 
LIBS += -lopengl32

all: test winapi_002_opengl


test:
	# OP: $(UNAME)

winapi_002_opengl: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
ifeq ($(UNAME), MINGW32_NT-6.1)
	./winapi_002_opengl.exe
else
	wine winapi_002_opengl.exe
endif

file:
	file winapi_002_opengl.exe

clean:
	rm -f *.o winapi_002_opengl
