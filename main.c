#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wave.h"
#include "spectrum.h"

/*
void printDft(spectrum_t *dft, int sampleRate, int steps)
{
  if (steps < 1 || steps > dft->k / 2)
    steps = dft->k / 2;

  int samplesPerStep = dft->k / 2 / steps;


  double sumSamples = 0;
  int samples = 0;
  for (int i = 0; i < dft->k / 2; i++) {

    if (samples > samplesPerStep) {
      // Calculate the frequency at the middle of our spectrum averaging sample
      double frequency = ((double)i - samplesPerStep/2)/dft->k * (float)sampleRate;

      // Calculate the magnitude at this frequency
      double magnitude = sumSamples / samples;

      // Maximum magnitude of a signal is the maximum possible sampled value? 2^15 (signed 16bits)
      // - I am not so sure about that...
      double dbAmplitude = 20 * log10(magnitude / (2^15));

      printf("Power @%.3f kHz: %.2f dB Magnitude: %8.0f ",
             frequency / 1000,
             dbPower,
             magnitude);
      for (int j = 0; j < dbPower; j++)
        putchar('#');
      putchar('\n');

      samples = 0;
      sumSamples = 0;
    }
    samples++;

    // magnitude = sqrt(a^2 + b^2)
    double magnitude = sqrt(pow(dft->spectrum_r[i],2) + pow(dft->spectrum_i[i], 2));
    sumSamples += magnitude;
  }
}*/

void printSpectrum(spectrum_t *s, int sampleRate)
{
  for (int i = 0; i < s->k / 2; i++) {
    // Calculate the frequency in the analog world
    double frequency = ((double)i)/s->k * (float)sampleRate;

    // Calculate the magnitude at this frequency
    // multiply by two because half of the power is at -frequency
    // and we want to measure it too.
    double magnitude = 2 * spectralMagnitude(s, i);

    // but I am not sure why we need to multiply twice by 2....
    magnitude *= 2;

    // Maximum magnitude of a signal is the maximum possible sampled value? 2^15 (signed 16bits)
    // - I am not so sure about that...
    double dbAmplitude = 20 * log10(magnitude / 1);

    printf("Power @%6.0f Hz: %7.2f dB Magnitude: %.5f ",
           frequency,
           dbAmplitude,
           magnitude);

    // One # for each dB above -100
    for (int j = -100; j < dbAmplitude; j++)
      putchar('#');
    putchar('\n');
  }
}


int main(int argc, char **argv) {
  printf("%s: sarfata fun adventures in the world of ffts\n", argv[0]);

  if (argc < 2) {
    fprintf(stderr, "Usage: %s <wave file>\n", argv[0]);
    exit(-1);
  }

  t_wavef *wave = openWave(argv[1]);
  debugWaveHeader(wave->header);


  spectrum_t *mydft = performDft((int16_t*)wave->audio, 4096, WINDOW_HANNING);
  printSpectrum(mydft, wave->header->sampleRate);
  //dumpSamples(wave, 11025);

  freeSpectrum(mydft);
  closeWave(wave);
  return 0;
}


