CC = gcc

LIBS = $(shell pkg-config --libs alsa)
CFLAGS = $(shell pkg-config --cflags alsa)

all: 45_alsa_sound_playback_2

45_alsa_sound_playback_2: src/main.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

run: 
	./45_alsa_sound_playback_2 44100 2 360 < sound.wav

clean:
	rm -f 45_alsa_sound_playback_2 *.o
