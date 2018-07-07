CC = gcc
LIBS += -lX11

all: 17_window_enter_background_red_leave_blue

17_window_enter_background_red_leave_blue: src/main.c
	$(CC) -o $@ $^ $(LIBS)

run: 
	./17_window_enter_background_red_leave_blue

clean:
	rm -f 17_window_enter_background_red_leave_blue *.o
