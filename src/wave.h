#include <math.h>

class Wave
{
public:
    Wave(float frequency, float sampleRate);
    float next();
private:
    float frequency;
    float sampleRate;
    int waveLength;
    int counter;
};