CC = gcc

LIBS += -lX11

all: 55_administration

55_administration: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	./55_administration

clean:
	rm -f 55_administration *.o
