#include <stdint.h>

typedef struct {
  uint16_t k;

  double *spectrum_r;
  double *spectrum_i;
} dft_t;

dft_t* performDft(uint16_t *audio, uint32_t length, uint16_t k);
void freeDft(dft_t*);
