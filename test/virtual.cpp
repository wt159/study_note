#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;

class A
{
public:
    virtual void addData()
    {
        cout << "A:" << __func__ << endl;
    }
public:
    A(/* args */){};
    ~A(){};
};

class B : public A
{
public:
    virtual void addData()
    {
        cout << "B:" << __func__ << endl;
        onProcessData();
    }
private:
    virtual void onProcessData() = 0;
public:
    B(/* args */){};
    ~B(){};
};

class C : public B
{
public:
    void putData()
    {
        cout << "C:" << __func__ << endl;
        addData();
    }
private:
    void onProcessData()
    {
        cout << "C:" << __func__ << endl;
    }
public:
    C(/* args */){};
    ~C(){};
};

void virtualTest1()
{
    C nTemp;
    cout << __func__ << endl;
    nTemp.putData();
}


int main()
{
    virtualTest1();
    return 0;
}