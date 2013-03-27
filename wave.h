#include <stdint.h> /* uint32_t */


typedef struct {
  /* RIFF chunk descriptor */
  char chunkId[4];
  uint32_t chunkSize;
  char chunkFormat[4];
  /* Sub-Chunk1: Format */
  uint32_t subChunk1Id;
  uint32_t formatSize;
  uint16_t audioFormat;
  uint16_t numChannels;
  uint32_t sampleRate;
  uint32_t byteRate;
  uint16_t blockAlign;
  uint16_t bitsPerSample;
  /* Sub-Chunk2: Data */
  uint32_t subChunk2Id;
  uint32_t audioSize;
} t_wave_header;

typedef struct {
  int fd;
  t_wave_header* header;
  uint8_t* audio;
} t_wavef;

t_wavef* openWave(const char *file);
void closeWave(t_wavef* wave);
void debugWaveHeader(t_wave_header *header);

uint32_t waveSamples(t_wave_header *header);
float waveDuration(t_wave_header *header);

void dumpSamples(t_wavef *wave, int count);
