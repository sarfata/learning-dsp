#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "wave.h"

#define WARN(format, ...) fprintf (stderr, format, ## __VA_ARGS__)

int readHeader(t_wavef*);
int readAudio(t_wavef*);

t_wavef* openWave(const char *file)
{
  int fd = open(file, O_RDONLY);
  if (!fd) {
    perror("Unable to open file");
    return NULL;
  }

  t_wavef *wave = malloc(sizeof(t_wavef));
  memset(wave, 0, sizeof(t_wavef));

  wave->fd = fd;

  if (!readHeader(wave))
  {
    readAudio(wave);
  }

  return wave;
}


void closeWave(t_wavef* wave)
{
  close(wave->fd);
  if (wave->header)
    free(wave->header);
  if (wave->audio)
    free(wave->audio);
  free(wave);
}

int readHeader(t_wavef* wave)
{
  ssize_t len;

  wave->header = malloc(sizeof(t_wave_header));
  memset(wave->header, 0, sizeof(t_wave_header));

  len = pread(wave->fd, wave->header, sizeof(t_wave_header), 0);
  if (len != sizeof(t_wave_header)) {
    WARN("Unable to read entire headers (%zi vs %zi)", len, sizeof(t_wave_header));
    return -1;
  }
  return 0;
}

int readAudio(t_wavef* wave)
{
  ssize_t len;

  wave->audio = malloc(wave->header->audioSize);
  len = pread(wave->fd, wave->audio, wave->header->audioSize, sizeof(t_wave_header));
  if (len != wave->header->audioSize) {
    WARN("Unable to read complete audio data (%zi vs %zi)", len, sizeof(wave->header->audioSize));
    return -1;
  }
  return 0;
}

uint32_t waveSamples(t_wave_header *header)
{
  return header->audioSize / header->blockAlign;
}

float waveDuration(t_wave_header *header)
{
  return waveSamples(header) * 1.0 / header->sampleRate;
}

void debugWaveHeader(t_wave_header *header)
{
  printf("ChunkId   : %.4s\n", header->chunkId);
  printf("Format    : %.4s\n\n", header->chunkFormat);

  printf("Audio Format: %i\n", header->audioFormat);
  printf("Num Channels: %i\n", header->numChannels);
  printf("Sample Rate: %i\n", header->sampleRate);
  printf("Byte Rate: %i\n", header->byteRate);
  printf("Block Align: %i\n", header->blockAlign);
  printf("BitsPerSample: %i\n\n", header->bitsPerSample);

  printf("Data size: %i\n", header->audioSize);

  printf("NumSamples: %i\n", waveSamples(header));
  printf("File duration: %f\n", waveDuration(header));
}

void dumpSamples(t_wavef *wave, int count)
{
  int16_t *audio = (int16_t*)wave->audio;

  for (int i = 0; i < count && i < waveSamples(wave->header); i++) {
    printf("audio[%i]: %02X%02X %i\n", i, wave->audio[i*2], wave->audio[i*2+1], audio[i]);
  }
}

