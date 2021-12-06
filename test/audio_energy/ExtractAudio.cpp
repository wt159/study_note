#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;

/* 48K 16bit */
void ExtractAudioChannel(char* data, int length, int curChannels, int extractStartChan, int extractChannels, char** destSrc, int& destLength)
{
    //48000 / 1000 * 20 * 2(byte) * 2(channels) = length
    const int sampleBitPer = 2;
    const int frame = length / curChannels / sampleBitPer;
    destLength = frame * extractChannels * sampleBitPer;
    char* dest = new char[destLength];
    int16_t* destPtr = (int16_t*) dest;
    int16_t* src = (int16_t*)data;

    for(int i = 0; i < frame; i++)
    {
        for(int j = 0; j < curChannels; j++)
        {
            if(j >= extractStartChan && j < (extractStartChan+ extractChannels)) {
                *destPtr = *src;
                destPtr++;
            }
            src++;
        }
    }


    *destSrc = (char*)dest;
}

void test_TheFirstThingToTest()
{
    const int frame = 48000/1000* 20;
    const int bitPer = 2;
    const int channels = 10;
    const int length = frame * bitPer * channels;
    char buf[length] = {0};
    int16_t *src = (int16_t*)buf;

    for(int i=0; i< frame; i++)
    {
        for(int j= 0; j< channels; j++)
        {
            *src = j;
            src++;
        }
    }

    char* dest = NULL;
    int destLen = 0;
    ExtractAudioChannel(buf, length, channels, 4, 2, &dest, destLen);

    if(dest) {
        cout << " destAddr:" << *(int16_t*)dest << " len:" << destLen << endl;
        for(int i = 0; i < 4; i++) {
            cout << "error value is " << *((int16_t*)dest + i) << endl;
        }
        delete[] dest;
    }

}

int main()
{
    test_TheFirstThingToTest();
    return 0;
}