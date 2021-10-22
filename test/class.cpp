#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;

class Base
{
private:
    int _num;
public:
    Base(/* args */) :_num(2) {}
    ~Base() {}
    void set(int num) { _num = num; }
    int get() { return _num; }
};

class A : public Base
{
public:
    static A& getInstance()
    {
        static A instance;
        return instance;
    }
private:
    /* data */
private:
    A(/* args */) {}
    ~A() {}
};

int main()
{
    cout<< A::getInstance().get() << endl;
    A::getInstance().set(5);
    cout << A::getInstance().get() << endl;
    return 0;
}