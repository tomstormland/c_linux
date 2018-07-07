CC = gcc

LIBS += -lX11

all: 06_draw_text

06_draw_text: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	./06_draw_text

clean:
	rm -f 06_draw_text *.o
