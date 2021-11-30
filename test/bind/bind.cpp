#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <functional>
#include <memory>


class TestClass2
{
public:
    TestClass2()
        :m_a(100)
    {}
public:
    int m_a;
};

typedef std::shared_ptr<TestClass2 *> typeClassPtr;
using TestClassPtr = std::shared_ptr<TestClass2 *>;

void func1()
{
    std::shared_ptr<TestClass2 *> TestClass2Ptr;
    typeClassPtr tp1 = TestClass2Ptr;
    TestClassPtr tp2 = tp1;
    *TestClass2Ptr = new TestClass2;
}

int main()
{
    TestClass2 test2;
    auto fun8 = std::bind(&TestClass2::m_a, std::placeholders::_1);

    int var = fun8(test2);
    std::cout << var << std::endl;
    
    return 0;
}