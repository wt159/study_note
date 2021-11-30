#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

void handleAudioConversion(void *destData, const int &destChan, const void *srcData, const int &srcChan)
{
    //deafult 16bits、 48K
    int len = srcChan * 8;

    int i, j;
    int num = 1;
    int16_t *inBuf = (int16_t *)srcData;
    int16_t *outBuf = (int16_t *)destData;

    if (destChan > srcChan) //2 -> 4
    {
        len = srcChan * 8;
        num = destChan / srcChan;
        printf("srcChan:%d, -> destChan:%d, len:%d, num:%d\n", srcChan, destChan, len, num);
        for (i = 0; i < len; ++i)
        {
            for (j = 0; j < destChan; ++j)
            {
                outBuf[i * num + j] = inBuf[i];
            }
        }
    }
    else if (destChan < srcChan) //2 -> 1
    {
        len = destChan * 8;
        num = srcChan / destChan;
        printf("srcChan:%d, -> destChan:%d, len:%d, num:%d\n", srcChan, destChan, len, num);
        for (i = 0; i < len; i++)
        {
            size_t sum = 0;
            for (j = 0; j < srcChan; ++j)
            {
                sum += inBuf[i * num + j];
            }
            outBuf[i] = sum / srcChan;
        }
    }
    else
    {
        memcpy(outBuf, inBuf, len);
    }
}

void printArr(int16_t *arr, int len)
{
    for (size_t i = 0; i < len; i++)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
}

void test()
{
    int16_t buf1[32];
    int16_t buf3[32];
    for (int i = 0; i < 32; i++)
        buf1[i] = i;

    int16_t buf2[64];
    for (int i = 0; i < 64; i++)
        buf2[i] = 2;

    printArr(buf1, 32);
    // printArr(buf2, 32);
    handleAudioConversion(buf2, 4, buf1, 1);
    printArr(buf2, 32);
    handleAudioConversion(buf3, 1, buf2, 4);
    printArr(buf3, 32);
}

int main()
{
    test();
    return 0;
}