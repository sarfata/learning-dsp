#include <math.h>
#include <stdlib.h>
#include "dft.h"

dft_t* performDft(uint16_t *audio, uint32_t length, uint16_t k)
{
  dft_t *dft = malloc(sizeof(dft_t));
  dft->k = k;
  dft->spectrum_r = malloc(sizeof(double) * k);
  dft->spectrum_i = malloc(sizeof(double) * k);

  for (uint16_t ki = 0; ki < k; ki++) {
    dft->spectrum_r[ki] = 0;
    dft->spectrum_i[ki] = 0;

    for (uint32_t i = 0; i < length; i++) {
      dft->spectrum_r[ki] += ((double)audio[i]) * cos(-2*M_PI*i*((float)ki)/k);
    }
  }
  return dft;
}

void freeDft(dft_t* dft)
{
  free(dft->spectrum_r);
  free(dft->spectrum_i);
  free(dft);
}
