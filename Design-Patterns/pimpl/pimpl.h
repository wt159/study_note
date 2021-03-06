#pragma once

// #define DEBUG 1

#ifdef DEBUG

class MyClass
{
public:
    MyClass();
    ~MyClass();

    void fun1();
    void fun2();

private:
    void fun3();
    void fun4();

    int a;
    int b;
}; 

#else
#include <memory>

// 降低耦合
// 信息隐藏
// 降低编译依赖，提高编译速度
// 接口与实现分离

class MyClass
{
public:
    MyClass();
    ~MyClass();

    void fun1();
    void fun2();

private:
    class MyClassImpl;
#ifdef USE_UNIQUE_PTR
    std::unique_ptr<MyClassImpl> pimpl;
#else
    MyClassImpl* pimpl;
#endif
    
};

#endif // DEBUG