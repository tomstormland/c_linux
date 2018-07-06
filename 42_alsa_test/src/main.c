#include <alsa/asoundlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

  int i;

  /* 01. print alsa library version */
  printf("01: ALSA Library Version: %s\n", SND_LIB_VERSION_STR);

  /* 02. print PCM stream types */
  printf("02: PCM stream types:\n");
  for (i=0; i<=SND_PCM_STREAM_LAST; i++) {
    printf("    - %s\n", snd_pcm_stream_name((snd_pcm_stream_t)i));
  }

  /* 03. print PCM access types */
  printf("03: PCM access types:\n");
  for (i=0; i<=SND_PCM_ACCESS_LAST; i++) {
    printf("    - %s\n", snd_pcm_access_name((snd_pcm_access_t)i));
  }

  /* 04. print PCM formats */
  printf("04: PCM formats:\n");
  for (i=0; i<=SND_PCM_FORMAT_LAST; i++) {
    if (snd_pcm_format_name((snd_pcm_format_t)i) != NULL) {
      printf("    - %s (%s)\n", snd_pcm_format_name((snd_pcm_format_t)i), snd_pcm_format_description((snd_pcm_format_t)i));
    }
  }

  /* 05: print PCM subformats */
  printf("05: PCM subformats:\n");
  for (i=0; i<=SND_PCM_SUBFORMAT_LAST; i++) {
    printf("    - %s (%s)\n", snd_pcm_subformat_name((snd_pcm_subformat_t)i), snd_pcm_subformat_description((snd_pcm_subformat_t)i));
  }

  /* 06: print PCM states */
  printf("06: PCM states:\n");
  for (i=0; i<=SND_PCM_STATE_LAST; i++) {
    printf("    - %s\n", snd_pcm_state_name((snd_pcm_state_t)i));
  }

  return 0;
}
