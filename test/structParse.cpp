#pragma once
#ifdef _WIN32
#include <WinSock2.h>
#else
#include <arpa/inet.h>
#endif
#include <string>
#include <iostream>
using std::cout;
using std::endl;

enum AudioDataType {
    AudioType_mic = 0,
    AudioType_ref,
    AudioType_out,
};

enum AudioDataFormat {
    audioFormat_16bit = 0,
    audioFormat_32bit,
    audioFormat_float,
};

enum ContentType {
    ContentType_msg = 0,
    ContentType_data,
};

struct AudioDataInfo {
    uint8_t audioType : 2; //0--mic 1--ref 2--out
    uint8_t channels : 4;
    uint8_t format : 2; //0--16bit 1--32bit 2--float
};

struct AudioMsgInfo {
    uint8_t id;
};

struct ContentHeader {
    uint8_t version;
    uint8_t reserved;
    uint8_t ctType;
    union ctInfo {
        struct AudioDataInfo dataInfo;
        struct AudioMsgInfo msgInfo;
    } ctInfo;
    uint32_t seqNum;
};

size_t  getContentHeadSize()
{
    ContentHeader head;
    size_t size = sizeof(head.version) + sizeof(head.reserved) + sizeof(head.ctType);
    size += sizeof(head.ctInfo.msgInfo.id) + sizeof(head.seqNum);
    return size;
}

template <typename T>
T htonl(T value) {
    return value;
}
template <typename T>
T ntohl(T value) {
    return value;
}
void showHeader(const ContentHeader& head)
{
    std::cout << "version:" << (int)head.version << "\n"
                <<"reserved:" << (int)head.reserved << "\n"
                <<"ctType:" << (int)head.ctType
                << std::endl;
    switch (head.ctType)
    {
    case ContentType_msg:
        cout << "msgID:" << (int)head.ctInfo.msgInfo.id << endl;
        break;
    case ContentType_data:
        cout << "dataChannels:" << (int)head.ctInfo.dataInfo.channels << endl;
        break;
    default:
        break;
    }
    cout << "seqNum:" << head.seqNum << "\n" << endl;
}
void  fillheader(uint8_t* destData, const size_t& destSize, const ContentHeader& head)
{
    size_t ops = 0;
    *destData = htonl(head.version);
    // printf("destData:%d\n", *destData);
    ops += sizeof(head.version);
    *(destData + ops) = htonl(head.reserved);
    ops += sizeof(head.reserved);
    *(destData + ops) = htonl(head.ctType);
    ops += sizeof(head.ctType);

    switch (head.ctType)
    {
    case ContentType_msg :
        *(destData + ops) = htonl(head.ctInfo.msgInfo.id);
        ops += sizeof(head.ctInfo.msgInfo.id);
        break;
    case ContentType_data :
        memcpy(destData + ops, &(head.ctInfo.dataInfo), sizeof(head.ctInfo.dataInfo));
        *(destData + ops) = htonl(*(destData+ops));
        ops += sizeof(head.ctInfo.dataInfo);
        break;
    default:
        break;
    }

    *(decltype(head.seqNum)*)(destData + ops) = htonl(head.seqNum);
    ops += sizeof(head.seqNum);
}
ContentHeader getHeader(const uint8_t* srcData, const size_t& srcSize)
{
    ContentHeader head;
    size_t ops = 0;
    head.version = ntohl(*srcData);
    ops += sizeof(head.version);
    // printf("srcData:%d, version:%d\n", *srcData, head.version);
    head.reserved = ntohl(*(srcData + ops));
    ops += sizeof(head.reserved);

    head.ctType = htonl(*(srcData + ops));
    ops += sizeof(head.ctType);
    
    switch (head.ctType)
    {
    case ContentType_msg :
        head.ctInfo.msgInfo.id = ntohl(*(srcData + ops));
        cout << "msgid:" << (int)head.ctInfo.msgInfo.id << " " << (int)(*(srcData+ops)) << endl; 
        ops += sizeof(head.ctInfo.msgInfo.id);
        break;
    case ContentType_data :
        uint8_t temp = *(srcData + ops);
        temp = ntohl(temp);
        memcpy(&(head.ctInfo.dataInfo), &temp, sizeof(head.ctInfo.dataInfo));
        ops += sizeof(head.ctInfo.dataInfo);
        break;
    }
    // showHeader(head);
    head.seqNum = *(decltype(head.seqNum)*)(srcData + ops);
    head.seqNum = ntohl(head.seqNum);
    ops += sizeof(head.seqNum);
    // showHeader(head);
    return head;
}
void  ContentPackage(uint8_t* destData, const size_t& destSize
        , const ContentHeader& head, const uint8_t* srcData, const size_t& srcSize)
{
    size_t ops = getContentHeadSize();
    if(destSize < (ops+srcSize)) {
        return;
    }
    cout << "destSize:" << destSize << " srcSize:" << srcSize << " ops:" << ops << endl;
    fillheader(destData, destSize, head);
    memcpy(destData + ops, srcData, srcSize);
}
void  ContentParse(uint8_t** destData, size_t& destSize
                , ContentHeader& head, const uint8_t* srcData, const size_t& srcSize)
{
    size_t ops = getContentHeadSize();
    
    head = getHeader(srcData, srcSize);
    // showHeader(head);
    *destData = (uint8_t*)srcData + ops;
    destSize = srcSize - ops;
}



void testmsg()
{
    char buf[] = "I am is xy";
    int bufLen = strlen(buf);
    ContentHeader head;
    head.version = 1;
    head.reserved = 2;
    head.ctType = ContentType_msg;
    head.ctInfo.msgInfo.id = 3;
    head.seqNum = 12345;

    size_t length = getContentHeadSize();
    showHeader(head);

    size_t destSize = length + bufLen + 1;
    char* pData = new char[destSize];
    ContentPackage((uint8_t*)pData, destSize, head, (uint8_t*)buf, bufLen);
    size_t strLen = bufLen;
    char* str = nullptr;
    ContentHeader temp;
    ContentParse((uint8_t**)&str, strLen, temp, (uint8_t*)pData, destSize);
    showHeader(temp);
    printf("ss,strlen:%d,destAddr:%p,%s, srcAddr:%p,%s\n", strLen, str, str, &pData[8], &pData[8]);
    cout << str << endl;

    delete[] pData;
}

void testdata()
{
    char buf[] = "I am is xy";
    int bufLen = strlen(buf);
    ContentHeader head;
    head.version = 1;
    head.reserved = 2;
    head.ctType = ContentType_data;
    head.ctInfo.dataInfo.audioType = AudioDataType::AudioType_mic;
    head.ctInfo.dataInfo.channels = 4;
    head.ctInfo.dataInfo.format = AudioDataFormat::audioFormat_16bit;
    head.seqNum = 12345;

    size_t length = getContentHeadSize();
    showHeader(head);

    size_t destSize = length + bufLen + 1;
    char* pData = new char[destSize];
    ContentPackage((uint8_t*)pData, destSize, head, (uint8_t*)buf, bufLen);
    size_t strLen = bufLen;
    char* str = new char[bufLen+1];
    ContentHeader temp;
    // ContentParse((uint8_t*)str, strLen, temp, (uint8_t*)pData, destSize);
    showHeader(temp);
    cout << str << endl;

    delete[] pData;
    delete[] str;
}

int main(int argc, const char** argv) 
{
    testmsg();
    // testdata();
    return 0;
}