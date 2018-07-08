.PHONY: test

UNAME := $(shell uname)

CC = i686-w64-mingw32-gcc

LIBS += -municode
LIBS += -mwindows 

all: test winapi_003_message_box

test:
	# OP: $(UNAME)

winapi_003_message_box: main.o
	$(CC) -o $@ $^ $(LIBS)

main.o: src/main.c
	$(CC) -o $@ -c $^

run:
ifeq ($(UNAME), MINGW32_NT-6.1)
	./winapi_003_message_box
else
	wine winapi_003_message_box.exe
endif

file:
	file winapi_003_message_box.exe

clean:
	rm -f *.o winapi_003_message_box
