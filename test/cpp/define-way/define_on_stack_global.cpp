#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <assert.h>
using namespace std;

class MyClass
{
public:
    MyClass(/* args */) {}
    ~MyClass() {}
    void *operator new(size_t size)
    {
        assert(false);
    }
    void operator delete(void *ptr)
    {
        assert(false);
    }

private:
    int a;
};

MyClass gtemp;

int main()
{
    MyClass stemp;
    MyClass *htemp = new MyClass;

    delete htemp;
    htemp = nullptr;
    return 0;
}