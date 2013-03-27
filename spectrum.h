#include <stdint.h>

#define WINDOW_NONE 0
#define WINDOW_HANNING 1

typedef struct {
  /* Number of samples in spectrum */
  uint32_t k;

  /* Real and Imaginary value of spectrum */
  double *spectrum_r;
  double *spectrum_i;
} spectrum_t;

/* Call this when you want to dispose of a spectrum object */
void freeSpectrum(spectrum_t*);

/* Returns a new spectrum object by performing a DFT on the 'length' first samples
 * of 'audio' data (16 bit LPCM).
 * The specified windowing function will be applied.
 */
spectrum_t* performDft(int16_t *audio, uint32_t length, int window);

/* Returns the spectral magnitude at given frequency. */
double spectralMagnitude(spectrum_t *s, int frequency);

/*
 * ASCII art representation of a spectrum.
 */
void printSpectrum(spectrum_t *s, int sampleRate);
