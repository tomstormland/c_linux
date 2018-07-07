CC = gcc

LIBS = $(shell pkg-config --libs alsa)
CFLAGS = $(shell pkg-config --cflags alsa)

all: 44_alsa_sound_playback

44_alsa_sound_playback: src/main.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

run: 
	./44_alsa_sound_playback < sound.wav

clean:
	rm -f 44_alsa_sound_playback *.o
