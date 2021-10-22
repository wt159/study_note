#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>
using namespace std;

class DMMessage
{
public:
    DMMessage(uint8_t aType) : type(aType){};
    virtual size_t getMsgSize() const
    {
        return 0;
    }
    virtual size_t writeToData(uint8_t *pData, size_t length) const
    {
        if (length < 5)
        {
            return 0;
        }

        *pData = type;

        return 5;
    }
    virtual size_t readFromData(uint8_t *pData, size_t length)
    {
        if (length < 5)
        {
            return 0;
        }

        type = *pData;
        if (type >= 0xf0)
        {
            type = 0xf0;
        }
        return 5;
    }
    uint8_t type;
    uint32_t resverd;
};

class DMUIMessage : public DMMessage
{
public:
    DMUIMessage() : DMMessage(6){};
    size_t getMsgSize() const
    {
        return content.length() + 1 + 5;
    }
    size_t writeToData(uint8_t *pData, size_t length) const
    {

        size_t ret = DMMessage::writeToData(pData, length);

        if (ret == 0)
        {
            return 0;
        }

        *((uint8_t *)(pData + ret)) = subType;

        if (length < content.length() + ret + 1)
        {
            return 0;
        }

        memcpy((uint8_t *)(pData + ret + 1), content.c_str(), content.length());

        return content.length() + ret + 1;
    }

    size_t readFromData(uint8_t *pData, size_t length)
    {

        size_t ret = DMMessage::readFromData(pData, length);

        if (ret == 0)
        {
            return 0;
        }

        subType = *((uint8_t *)(pData + ret));
        content.assign((const char *)(pData + ret + 1), length - ret - 1);

        return length;
    }
    uint8_t subType;
    std::string content;
};

void prin_message(const DMUIMessage& message)
{
    printf("DMUIMessage info : \n");
    printf("length:%llu\n", message.getMsgSize());
    printf("type:%d\n", message.type);
    printf("subType:%d\n", message.subType);
    printf("content:%s\n", message.content.c_str());
}



void test_message(const DMMessage &message)
{
    
        size_t msgSize = message.getMsgSize();
        //to prevent some message not to impl getMsgSize()
        //TCP_Type:4 TCP_Length:4
        msgSize += 4 + 4;

        uint8_t *buf = (uint8_t*)malloc(msgSize);
        size_t len = message.writeToData(buf + 4 + 4, msgSize - 4 - 4);
        
        DMUIMessage temp;
        // temp.readFromData(buf + 4 + 4, msgSize - 4 - 4);
        temp.readFromData(buf + 4 + 4, len);
        prin_message(temp);

        free(buf);
        buf = nullptr;
}

int main()
{
    DMUIMessage messages;
    messages.content = "test message";
    messages.subType = 2;
    prin_message(messages);
    cout << "--------split line---------" << endl;
    test_message(messages);
    return 0;
}