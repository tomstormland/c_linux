#include <alsa/asoundlib.h>
#include <stdio.h>

/* use newer alsa api */
#define ALSA_PCM_NEW_HW_PARAMS_API

int main(int argc, char *argv[]) {

  int rc;
  int i;

  snd_pcm_t* handle;
  snd_pcm_hw_params_t* params;

  unsigned int a, b;

  int dir;

  snd_pcm_uframes_t frames;

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

  /* open PCM device for playback */
  rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);

  if (rc < 0) {
    printf("ERROR: Unable to open pcm device: %s.\n", snd_strerror(rc));
    return -1;
  }

  /* allocate hardware parameters object */
  snd_pcm_hw_params_alloca(&params);

  /* fill it in with default values. */
  snd_pcm_hw_params_any(handle, params);

  /* set the desired hardware parameters. */

  /* interleaved mode */
  snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);

  /* signed 16-bit little-endian format */
  snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);

  /* two channels (stereo) */
  snd_pcm_hw_params_set_channels(handle, params, 2);

  /* 44100 bits/second sampling rate (CD quality) */
  i = 44100;
  snd_pcm_hw_params_set_rate_near(handle, params, &i, &dir);

  /* write the parameters to the drive */
  rc = snd_pcm_hw_params(handle, params);

  if (rc < 0) {
    printf("ERROR: Unable to set hw parameters: %s.\n", snd_strerror(rc));
    return -1;
  }

  /* display information about the PCM interface */

  printf("A01: PCM handle name = '%s'.\n", snd_pcm_name(handle));
  printf("A02: PCM state = '%s'.\n", snd_pcm_state_name(snd_pcm_state(handle)));

  snd_pcm_hw_params_get_access(params, (snd_pcm_access_t *)&i);
  printf("A03: access type = '%s'.\n", snd_pcm_access_name((snd_pcm_access_t)i));

  snd_pcm_hw_params_get_format(params, &i);
  printf("A04: format = '%s' (%s).\n", snd_pcm_format_name((snd_pcm_format_t)i), snd_pcm_format_description((snd_pcm_format_t)i));

  snd_pcm_hw_params_get_subformat(params, (snd_pcm_subformat_t*)&i);
  printf("A05: subformat = '%s' (%s).\n", snd_pcm_subformat_name((snd_pcm_subformat_t)i), snd_pcm_subformat_description((snd_pcm_subformat_t)i));

  snd_pcm_hw_params_get_channels(params, &i);
  printf("A06: channels = %d.\n", i);

  snd_pcm_hw_params_get_rate(params, &i, &dir);
  printf("A07: rate = %d bps (beats per second).\n", i);

  snd_pcm_hw_params_get_period_time(params, &i, &dir);
  printf("A08: period time = %d us.\n", i);

  snd_pcm_hw_params_get_period_size(params, &frames, &dir);
  printf("A09: period size = %d frames.\n", (int)frames);

  snd_pcm_hw_params_get_buffer_time(params, &i, &dir);
  printf("A10: buffer time = %d us.\n", i);

  snd_pcm_hw_params_get_buffer_size(params, (snd_pcm_uframes_t*)&i);
  printf("A11: buffer size = %d frames.\n", i);

  snd_pcm_hw_params_get_periods(params, &i, &dir);
  printf("A12: periods per buffer = %d frames.\n", i);

  snd_pcm_hw_params_get_rate_numden(params, &a, &b);
  printf("A13: exact rate = %d/%d bps.\n", a, b);

  i = snd_pcm_hw_params_get_sbits(params);
  printf("A14: significant bits = %d.\n", i);

  /* deprecated */
  // snd_pcm_hw_params_get_tick_time(params,&i, &dir);
  // printf("A15: tick time = %d us.\n", i);

  i = snd_pcm_hw_params_is_batch(params);
  printf("A15: is batch = %d.\n", i);

  i = snd_pcm_hw_params_is_block_transfer(params);
  printf("A16: is block transfer = %d.\n", i);

  i = snd_pcm_hw_params_is_double(params);
  printf("A17: is double = %d.\n", i);

  i = snd_pcm_hw_params_is_half_duplex(params);
  printf("A18: is half duplex = %d.\n", i);

  i = snd_pcm_hw_params_is_joint_duplex(params);
  printf("A19: is joint duplex = %d.\n", i);

  i = snd_pcm_hw_params_can_overrange(params);
  printf("A20: can overrange = %d.\n", i);

  i = snd_pcm_hw_params_can_mmap_sample_resolution(params);
  printf("A21: can mmap = %d.\n", i);

  i = snd_pcm_hw_params_can_pause(params);
  printf("A22: can pause = %d.\n", i);

  i = snd_pcm_hw_params_can_resume(params);
  printf("A23: can resume = %d.\n", i);

  i = snd_pcm_hw_params_can_sync_start(params);
  printf("A24: can sync start = %d.\n", i);

  snd_pcm_close(handle);

  return 0;
}
