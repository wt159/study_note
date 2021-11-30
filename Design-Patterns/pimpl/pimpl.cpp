#include "pimpl.h"
#include <iostream>

using namespace std;

#ifdef DEBUG

MyClass::MyClass()
    : a(1), b(2)
{
}

MyClass::~MyClass()
{
}

void MyClass::fun1()
{
    fun3();
}
void MyClass::fun2()
{
    fun4();
}
void MyClass::fun3()
{
    cout << "a is " << a << endl;
}
void MyClass::fun4()
{
    cout << "b is " << b << endl;
}

#else

class MyClass::impl
{
public:
    impl();
    ~impl();

    void fun1();
    void fun2();

private:
    void fun3();
    void fun4();

private:
    int a;
    int b;
};

MyClass::impl::impl()
    : a(1), b(2)
{
}

MyClass::impl::~impl()
{
}

void MyClass::impl::fun1()
{
    fun3();
}
void MyClass::impl::fun2()
{
    fun4();
}
void MyClass::impl::fun3()
{
    cout << "pimpl a is " << a << endl;
}
void MyClass::impl::fun4()
{
    cout << "pimpl b is " << b << endl;
}

MyClass::MyClass() : pimpl(new impl)
{
}

MyClass::~MyClass()
{
    if(pimpl)
        delete pimpl;
    pimpl = nullptr;
}

void MyClass::fun1()
{
    pimpl->fun1();
}

void MyClass::fun2()
{
    pimpl->fun2();
}

#endif