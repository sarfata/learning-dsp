#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wave.h"
#include "spectrum.h"

int main(int argc, char **argv) {
  t_wavef *wave;
  spectrum_t *mydft;
  int length;

  printf("%s: put some DSP classes to work\n", argv[0]);

  if (argc < 3) {
    fprintf(stderr, "  Usage: %s <wave file> <samples to dft>\n", argv[0]);
    fprintf(stderr, "  Example: %s samples/sine-3200.wav 512\n", argv[0]);
    exit(-1);
  }

  length = atoi(argv[2]);

  wave = openWave(argv[1]);
  debugWaveHeader(wave->header);


  mydft = performDft((int16_t*)wave->audio, length, WINDOW_HANNING);
  printSpectrum(mydft, wave->header->sampleRate);
  //dumpSamples(wave, 11025);

  freeSpectrum(mydft);
  closeWave(wave);
  return 0;
}


