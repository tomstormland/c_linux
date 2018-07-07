CC = gcc

LIBS += -lxcb
LIBS += -lxcb-icccm

all: 53_xcb_window

53_xcb_window: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run:
	./53_xcb_window

clean:
	rm -f *.o 53_xcb_window
