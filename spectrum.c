#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "spectrum.h"

/* Returns a new spectrum object by performing a DFT on the 'length' first samples
 * of 'audio' data (16 bit LPCM).
 * The specified windowing function will be applied.
 *
 * Knowing that the input is real, we can simplify and only do K/2 frequencies
 * because S(-f) = S*(f) = S(f) (when signal is real only.)
 * This reduces the number of computations by 2 but this is still a O(N^2) algorithm.
 */
spectrum_t* performDft(int16_t *audio, uint32_t length, int window)
{
  spectrum_t *s = malloc(sizeof(spectrum_t));
  s->k = length;
  s->spectrum_r = malloc(sizeof(double) * length);
  s->spectrum_i = malloc(sizeof(double) * length);

  // For each frequency
  for (uint32_t ki = 0; ki < length / 2; ki++) {
    s->spectrum_r[ki] = 0;
    s->spectrum_i[ki] = 0;

    // Sum 0 to N of s(t)*exp(-2*j*pi*k*n/N)
    for (uint32_t i = 0; i < length; i++) {
      // Normalize sample to be a number between -1 and 1.
      double sample = audio[i] / (double)32768;

      // If hanningWindow enabled, apply the hanning Window function to the signal
      if (window == WINDOW_HANNING)
        sample *= (double)1/2*(1-cos(2*M_PI*((double)i)/length));

      s->spectrum_r[ki] += sample * cos(-2*M_PI*i*((float)ki)/length);
      s->spectrum_i[ki] += sample * sin(-2*M_PI*i*((float)ki)/length);
    }

    // Divide by the number of samples.
    s->spectrum_r[ki] = s->spectrum_r[ki] / length;
    s->spectrum_i[ki] = s->spectrum_i[ki] / length;
  }

  // TODO: it would be nice to either fill the second half of the spectrum
  // (by copying value at lower values) or malloc() a smaller spectrum.
  // I am not sure which one is best now - so doing nothing.
  return s;
}

/* Returns the spectral magnitude at given frequency. */
double spectralMagnitude(spectrum_t *s, int frequency)
{
  if (frequency >= s->k)
    return 0;

  // magnitude = sqrt(a^2 + b^2)
  return sqrt(pow(s->spectrum_r[frequency],2) + pow(s->spectrum_i[frequency], 2));
}

/* Call this when you want to dispose of a spectrum object */
void freeSpectrum(spectrum_t* s)
{
  free(s->spectrum_r);
  free(s->spectrum_i);
  free(s);
}

/*
 * ASCII art representation of a spectrum.
 */
void printSpectrum(spectrum_t *s, int sampleRate)
{
  for (int i = 0; i < s->k / 2; i++) {
    // Calculate the frequency in the analog world
    double frequency = ((double)i)/s->k * (float)sampleRate;

    // Calculate the magnitude at this frequency
    // multiply by two because half of the power is at -frequency
    // and we want to measure it too.
    double magnitude = 2 * spectralMagnitude(s, i);

    // AHEM - but I am not sure why we need to multiply twice by 2....
    magnitude *= 2;

    // Amplitude in dB - This is a factor of the magnitude to the max value (1)
    // so the amplitude in dB will always be a negative number.
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
