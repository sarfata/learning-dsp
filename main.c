#include <stdio.h>
#include <stdlib.h>
#include "wave.h"
#include "dft.h"

int main(int argc, char **argv) {
  printf("%s: sarfata fun adventures in the world of ffts\n", argv[0]);

  if (argc < 2) {
    fprintf(stderr, "Usage: %s <wave file>\n", argv[0]);
    exit(-1);
  }

  t_wavef *wave = openWave(argv[1]);
  debugWaveHeader(wave->header);


  dft_t *mydft = performDft((uint16_t*)wave->audio, 1024, 1024);


  freeDft(mydft);
  closeWave(wave);
  return 0;
}


