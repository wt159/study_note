#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <memory>
#include <string.h>

using std::cout;
using std::endl;

void func1()
{
    std::auto_ptr<int> a;
    *a = 1;
    cout << "a.get():" << a.get() << endl;
    cout << *a << endl;
}

int main()
{
    // func1();
    cout << sizeof(int) << endl;
    cout << (int)(~0) << endl;
    cout << (unsigned short)(~0) << endl;
    return 0;
}