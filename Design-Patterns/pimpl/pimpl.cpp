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

class MyClass::MyClassImpl
{
public:
    MyClassImpl();
    ~MyClassImpl();

    void fun1();
    void fun2();

private:
    void fun3();
    void fun4();

private:
    int a;
    int b;
};

MyClass::MyClassImpl::MyClassImpl()
    : a(1), b(2)
{
}

MyClass::MyClassImpl::~MyClassImpl()
{
}

void MyClass::MyClassImpl::fun1()
{
    fun3();
}
void MyClass::MyClassImpl::fun2()
{
    fun4();
}
void MyClass::MyClassImpl::fun3()
{
    cout << "pimpl a is " << a << endl;
}
void MyClass::MyClassImpl::fun4()
{
    cout << "pimpl b is " << b << endl;
}

MyClass::MyClass() : pimpl(new MyClassImpl)
{
}

MyClass::~MyClass()
{
    
#ifdef USE_UNIQUE_PTR
    
#else
    if(pimpl)
        delete pimpl;
    pimpl = nullptr;
#endif
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