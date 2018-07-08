.PHONY: test

UNAME := $(shell uname)

CC = i686-w64-mingw32-gcc

LIBS += -municode
LIBS += -mwindows 

all: test winapi_006_username

test:
	# OP: $(UNAME)
	file winapi_006_username.exe

winapi_006_username: main.o
	$(CC) -o $@ $^ $(LIBS)

main.o: src/main.c
	$(CC) -o $@ -c $^

run:
ifeq ($(UNAME), MINGW32_NT-6.1)
	./winapi_006_username
else
	wine winapi_006_username.exe
endif

file:
	file winapi_006_username.exe

clean:
	rm -f *.o winapi_006_username.exe
