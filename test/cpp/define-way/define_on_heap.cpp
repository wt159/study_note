#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <memory>
using namespace std;

class MyClass
{
public:
    static MyClass *create(int num = 0)
    {
        return new MyClass(num);
    }
    void destory()
    {
        delete this;
    }

public:
    void print()
    {
        cout << " zhe a is " << a << endl;
    }

protected:
    MyClass() : a(0) {}
    MyClass(int num) : a(num) {}
    ~MyClass() {}

private:
    int a;
};

// MyClass temp1;  error

int main()
{
    // MyClass temp;    error
    // shared_ptr<MyClass> tempPtr = make_shared<MyClass>();    error
    MyClass *temp2 = MyClass::create();
    temp2->print();
    temp2->destory();
    temp2 = nullptr;
    return 0;
}