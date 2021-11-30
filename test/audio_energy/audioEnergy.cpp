#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <string.h>
#include <assert.h>
#include <math.h>

using namespace std;

#define MAX_CONTINUOUS_ABNORMAL (5*50)

typedef struct _AudioEnergyInfo
{
    uint16_t continuousAbnormalSum;
    int      curEnergy;
    int      minEnergy;
    int      maxEnergy;
    int      aveEnergy;
}AudioEnergyInfo;

#define MAX_AUDIO_CHANNELS (8)


class AudioEnergyStatistics
{
public:
    AudioEnergyStatistics() = delete;
    AudioEnergyStatistics(int maxChannels) : _maxChannels(maxChannels)
    {
        assert(_maxChannels > MAX_AUDIO_CHANNELS);
        memset(&_audioEnergy, 0, sizeof(AudioEnergyInfo) * MAX_AUDIO_CHANNELS);
    }
    AudioEnergyStatistics(AudioEnergyStatistics &&) = default;
    AudioEnergyStatistics(const AudioEnergyStatistics &) = default;
    AudioEnergyStatistics &operator=(AudioEnergyStatistics &&) = default;
    AudioEnergyStatistics &operator=(const AudioEnergyStatistics &) = default;
    ~AudioEnergyStatistics();

private:
    int calAudioEnergy(int16_t* data, int len)
    {
        double sum = 0;

        if (len <= 0)
        {
            return 0;
        }

        int numOfSamples = len / sizeof(short);

        for (int i = 0; i < numOfSamples; i++)
        {
            sum += data[i] * data[i];
        }

        sum = sum / numOfSamples;

        int db = 10 * log10(sum + 1);

        return db;
    }

private:
    int _maxChannels;
    AudioEnergyInfo _audioEnergy[MAX_AUDIO_CHANNELS];
};

int main()
{
    
    return 0;
}