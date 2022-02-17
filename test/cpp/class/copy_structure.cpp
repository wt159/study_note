#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;


class A
{
private:
    char *_data;
public:
    A(/* args */):_data(nullptr)
    { 
        _data = new char[32];
    }
    ~A()
    {
        if(_data != nullptr)
        {
            delete[] _data;
        }
    }
    void showDataAddr()
    {
        std::cout << (int *)_data << std::endl;
    }
};

void func1()
{
    A test1;
    test1.showDataAddr();
    A test2(test1);
    test2.showDataAddr();
}

enum myenum 
{
    a = 0,
    b,
    c = 0xFF,
};

struct enumTest
{
    myenum mye;
};
struct uint8Test
{
    uint8_t myi;
};

void test()
{
    enumTest temp;
    uint8Test temp1;
    temp.mye = myenum::a;
    cout << sizeof(struct enumTest) << endl;
    cout << sizeof(temp) << endl;
    cout << sizeof(temp1) << endl;
}

int main()
{
    // func1();
    test();
    return 0;
}