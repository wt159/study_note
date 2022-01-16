#include <iostream>

class A
{
public:
    A()
    {
        std::cout << "call A constructor" << std::endl;
    }

    ~A()
    {
        std::cout << "call A destructor" << std::endl;
    }
};

int main(int argc, char *argv[])
{

    A *p = (A *)::operator new(sizeof(A)); //分配

    new (p) A(); //构造

    p->~A(); //析构

    ::operator delete(p); //释放

    return 0;
}