#include "wave.h"

Wave::Wave(float frequency, float sampleRate)
{
    this->frequency = frequency;
    this->sampleRate = sampleRate;
    this->waveLength = (int)(sampleRate / frequency);
    this->counter = 0;
}

float Wave::next()
{
    // Reset counter after each cycle
    counter = (counter + 1) % waveLength;

    return sin(2 * M_PI * frequency * (counter / sampleRate));
}
