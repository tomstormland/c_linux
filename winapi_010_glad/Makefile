.PHONY: test

UNAME := $(shell uname)

CC = i686-w64-mingw32-gcc

CFLAGS += -municode
CFLAGS += -mwindows 
CFLAGS += -I GL/include

LIBS += -lopengl32

all: test winapi_010_glad.exe

test:
	# OP: $(UNAME)

winapi_010_glad.exe: glad.o main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: src/main.c
	$(CC) $(CFLAGS) -o $@ -c $^

glad.o: GL/src/glad.c
	$(CC) $(CFLAGS) -o $@ -c $^

run:
ifeq ($(UNAME), MINGW32_NT-6.1)
	./winapi_010_glad.exe
else
	wine winapi_010_glad.exe
endif

file:
	file winapi_010_glad.exe

clean:
	rm -f *.o winapi_002_opengl
