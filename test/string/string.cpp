#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <memory>
using namespace std;

void test(std::string &a)
{
    std::string temp = "aaaaaa";
    a = temp;
}

void test11(
    int len)
{
    cout << "len:" << len << endl;
    int size = len;
    {
        char str[size];
        char temp;
        cout << "addr:" << (int *)str << endl;
        cout << "temp:" << (int *)&temp << endl;
        cout << "size:" << sizeof(str) << endl;
        memcpy(str, "hello isssssssssssssasdfsacsacascsacdsadcsdcadcacdasdcasdcscssssss", len);
        cout << "str:" << str << endl;
    }
}

// void test3()
// {
//     char* p = (char*)malloc(0);
//     char* p1 = NULL;
//     // memcpy(p1, "aaa", 3);
// }

int main()
{
    int len = 33;
    // string s = "test";
    // char data[len];
    // test(s);
    test11(len);
    // cout << s << endl;
    // test3();
    // cout << "end" << endl;
    return 0;
}