#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <string.h>

#define MIC_INFO(fmt, ...) printf(fmt "\n", ##__VA_ARGS__)

#pragma pack(push)
#pragma pack(1)

struct WaveFileHead
{
	uint8_t        RiffID [4];
    uint32_t       RiffSize;
    uint8_t        WaveID[4];
    uint8_t        FmtID[4];
    uint32_t       FmtSize;
    uint16_t       wFormatTag;
    uint16_t       nChannels;
    uint32_t       nSamplesPerSec;  /*采样频率*/
    uint32_t       nAvgBytesPerSec; /*每秒所需字节数*/
    uint16_t       nBlockAlign; /*数据块对齐单位,每个采样需要的字节数*/
    uint16_t       wBitsPerSample;/*每个采样需要的bit数*/
    uint8_t        DataID[4];
    uint32_t       nDataBytes;
};

#pragma pack(pop)

class wavFile
{
private:
    WaveFileHead _head;
    FILE* _fp = NULL;
    std::string _fileName = "";
public:
    wavFile(const char* fileName) : _fileName(fileName)
    {
        _fp = fopen(fileName, "a+");
        // fseek(_fp, 0, SEEK_SET);
        rewind(_fp);
        if(_fp)
        {
            memset(&_head, 0, sizeof(_head));
            fread(&_head, sizeof(_head), 1, _fp);
            MIC_INFO("wav file header size is %d", sizeof(_head));
            printHeadInfo(_head);
        }
        else
        {
            printf("fopen file[%s] error!\n", fileName);
        }
    }
    ~wavFile()
    {
        if(_fp)
            fclose(_fp);
        MIC_INFO("fclose file[%s] !", _fileName.c_str());
    }
    void printHeadInfo(WaveFileHead& head)
    {
        MIC_INFO("file name is %s", _fileName.c_str());
        MIC_INFO("wavFileTest:RiffID:%c%c%c%c", head.RiffID[0], head.RiffID[1], head.RiffID[2], head.RiffID[3]);
        MIC_INFO("wavFileTest:RiffSize:%d", head.RiffSize);
        MIC_INFO("wavFileTest:WaveID:%c%c%c%c", head.WaveID[0], head.WaveID[1], head.WaveID[2], head.WaveID[3]);
        MIC_INFO("wavFileTest:FmtID:%c%c%c%c", head.FmtID[0], head.FmtID[1], head.FmtID[2], head.FmtID[3]);
        MIC_INFO("wavFileTest:FmtSize:%d", head.FmtSize);
        MIC_INFO("wavFileTest:wFormatTag:%d", head.wFormatTag);
        MIC_INFO("wavFileTest:nChannels:%d", head.nChannels);
        MIC_INFO("wavFileTest:nSamplesPerSec:%d", head.nSamplesPerSec);
        MIC_INFO("wavFileTest:nAvgBytesPerSec:%d", head.nAvgBytesPerSec);
        MIC_INFO("wavFileTest:nBlockAlign:%d", head.nBlockAlign);
        MIC_INFO("wavFileTest:wBitsPerSample:%d", head.wBitsPerSample);
        MIC_INFO("wavFileTest:DataID:%c%c%c%c", head.DataID[0], head.DataID[1], head.DataID[2], head.DataID[3]);
        MIC_INFO("wavFileTest:nDataBytes:%d", head.nDataBytes);
        MIC_INFO("--------------------------------------------------------");
    }
};

int main(int argc, char const *argv[])
{
    wavFile wav("speaker.wav");
    wavFile wav1("MicIn.wav");
    wavFile wav2("MicOut.wav");
    wavFile wav3("SpkIn.wav");
    wavFile wav4("voice_tone_stereo.wav");
    return 0;
}
