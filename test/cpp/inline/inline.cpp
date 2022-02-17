#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;

class A
{
public:
    void doA() { cout << "doA" << endl; }
    void do_not_inline();
    void doInline();
};

inline void A::doInline()
{
    cout << "do inline" << endl;
}
void A::do_not_inline()
{
    cout << "do not inline" << endl;
}

int main()
{
    A a;
    a.doA();
    a.doInline();
    a.do_not_inline();
    return 0;
}