#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

using std::cout;
using std::endl;

struct wei {
    char a;
    int b;
};

void test11(int numProcess)
{
    std::string able;
    std::stringstream ss;
    std::string agc("AGC:");
    std::string ans("ANS:");
    std::string aec("AEC:");
    std::string btrue("true,");
    std::string bfalse("false,");
    cout << agc << ans << aec << btrue << bfalse << endl;
    switch(numProcess)
    {
        case 0:
        {
            able = agc + btrue + ans + bfalse + aec + bfalse;
            ss << agc << btrue << ans << bfalse << aec << bfalse;
        }
        break;
        case 1:
        {
            able = agc + btrue + ans + btrue + aec + bfalse;
            ss << agc << btrue << ans << btrue << aec << bfalse;
        }
        break;
        case 2:
        {
            able = agc + btrue + ans + btrue + aec + btrue;
            ss << agc << btrue << ans << btrue << aec << btrue;
        }
        break;
        default:
        break;
    }
    cout << "able str:" << able  << endl;
    cout << "ss str:" << ss.str().c_str() << endl;
}

std::string getAddrId(std::string key, int id)
{
    std::stringstream ss;
    ss << key << ":" << id;
    return ss.str();
}

char *getAddrStr()
{
    const char *ip = "192.24.12.6";
    int port = 30000;
    std::string key = getAddrId(ip, port);
    std::string str = getAddrId(key, 1);
    int len = str.length();
    std::cout << "addrstr len:" << len << std::endl;
    char* buf = new char[len+1];
    memmove(buf, str.c_str(), len);
    buf[len] = 0;
    return buf;
}

void func()
{
    std::string a = " enable play audio";
    std::string b = " disable play audio";

    std::cout << a.rfind("enable") << std::endl;
    std::cout << a.rfind("disable") << std::endl;
    std::cout << b.rfind("enable") << std::endl;
    std::cout << b.rfind("disable") << std::endl;
}

void funa()
{
    std::string a = " enable play audio";
    std::string b = " disable play audio";

    std::cout << a.size() << std::endl;
    std::cout << a.length() << std::endl;
    std::cout << b.size() << std::endl;
    std::cout << b.length() << std::endl;

    std::string c;
    char buf[] = "hello xylink";
    // char cStr[msgLen] = { 0 };
    // memmove(cStr, pMsgData + 1, msgLen - 1);
    // msg.msgContent = cStr;
    int len = 10;
    char* cStr = new char[len];
    memset(cStr, 0, len);
    memmove(cStr, buf + 1, len);
    c = cStr;
    std::cout << "str:" << c << std::endl;
    std::cout << "size:" << c.size() << std::endl;
    std::cout << "len:" << c.length() << std::endl;
    delete[] cStr;
    func();

    std::cout << sizeof(std::string::size_type) << std::endl;

    char *p = getAddrStr();

    printf("%s\n", p);
}
void fun1()
{
    std::string s = "0  ";
    printf("%s ", s.c_str());
    std::cout <<  s.size() << " " << s.length() << " " << s.empty() << std::endl;
}

void test1()
{
    std::string s;
    const char *a = "hello";
    s = a;
    printf("size:%d,len:%d,str:%s\n", s.size(), s.length(), s.c_str());
    printf("sizeof(long long):%d, %llu,%d", sizeof(uint64_t), (uint64_t)10000000000000000, (uint64_t)200000000000000000);
}
int main()
{
    
    test11(2);

    return 0;
}