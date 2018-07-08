.PHONY: test

UNAME := $(shell uname)

CC = i686-w64-mingw32-gcc

LIBS += -municode
LIBS += -mwindows 

all: test winapi_005_computer_name

test:
	# OP: $(UNAME)

winapi_005_computer_name: main.o
	$(CC) -o $@ $^ $(LIBS)

main.o: src/main.c
	$(CC) -o $@ -c $^

run:
ifeq ($(UNAME), MINGW32_NT-6.1)
	./winapi_005_computer_name
else
	wine winapi_005_computer_name.exe
endif

file:
	file winapi_005_computer_name.exe

clean:
	rm -f *.o winapi_005_computer_name
