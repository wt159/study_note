#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <memory>
#include <queue>

using namespace std;

typedef std::shared_ptr<int> SamplePtr;

class Buffer
{
public:
    Buffer(int bufferCapacity)
        : _buffer()
        {}
    virtual ~Buffer()
    {
        auto size = _buffer.size();
        for(int i = 0; i < size; ++i) {
            _buffer.pop();
        }
    }

    bool putData(void *pData, int length)
    {
        SamplePtr sample = std::make_shared<int>(length);
        _buffer.emplace(sample);
        return true;
    }

    bool putData(SamplePtr &data)
    {
        _buffer.emplace(data);
        return true;
    }
    void getData(SamplePtr &data)
    {
        
        if(!_buffer.empty())
        {   
            data = _buffer.front();
            _buffer.pop();
        }
    }

private:
    std::queue<SamplePtr> _buffer;
};

class MyBuffer : protected Buffer
{
public:
    MyBuffer(int &param, int bufferCapacity)
        : Buffer(bufferCapacity)
        , _param(param)
    {
    }
    virtual ~MyBuffer() { }

    bool putData(void *pData, int length)
    {
        return Buffer::putData(pData, length);
    }
    void getData(SamplePtr &data, bool isPeople)
    {
        if(_param < 5) {
            cout << " ... " << endl;
        } else {
            cout << ",,," << endl;
        }

        if(isPeople) {
            cout << "isPeople" << endl;
        } else {
            cout << "isContent" << endl;
        }

        Buffer::getData(data);
    }

private:
    const int& _param;
};

void testbuffer()
{
    int maxLen = 10;
    char buf[maxLen];
    Buffer base(maxLen);

    for(int i=0; i<maxLen; i++) {
        base.putData(buf, i);
    }


    SamplePtr data;
    for(int i=0; i<maxLen; i++) {
        base.getData(data);
        cout << *data << endl;
    }
}

void myBufferTest()
{
    int maxLen = 10;
    char buf[maxLen];

    MyBuffer buffer(maxLen, maxLen);

    for(int i=0; i<maxLen; i++) {
        buffer.putData(buf, i);
    }


    SamplePtr data;
    for(int i=0; i<maxLen; i++) {
        buffer.getData(data, (i%2?true:false));
        cout << *data << endl;
    }
}

int main()
{
    testbuffer();
    cout << "---------------------" << endl;
    myBufferTest();
    return 0;
}