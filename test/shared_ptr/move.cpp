#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <memory>

using std::cout;
using std::endl;


struct TestStruct
{
    int num;
};

class B
{
private:
    int _num;
public:
    B(int num): _num(num) {}
    ~B();
    void show() { cout << _num << endl; }
};

struct MoveGroup
{
    B *_cl;
    TestStruct *ts;
};

std::map<int, std::shared_ptr<MoveGroup>> _testMap;


void test1(const TestStruct& t)
{
    cout << t.num << endl;
}

void testMove()
{
    // static MoveGroup temp;
    int add = 2;

    MoveGroup temp;
    temp.ts = new TestStruct;
    temp.ts->num = 1;
    temp._cl = new B(2);

    test1(*(temp.ts));
    temp._cl->show();

    cout << &add << endl;
    cout << &temp << endl;
    cout << temp.ts << endl;
    cout << temp._cl << endl;
    // _testMap[0] = std::move(temp);
    _testMap[0] = std::make_shared<MoveGroup>(temp);
}

#ifdef NULL
#undef NULL
#define NULL (void*)0
#endif


void test1()
{
    
}

int main()
{
    testMove();

    auto iter = _testMap.begin();

    cout << " map second addr:" << endl;
    cout << &iter->second << endl;
    cout << &iter->second->ts << endl;
    cout << iter->second->_cl << endl;

    if(iter->second->_cl == nullptr) {
        cout << " nullptr" << endl;
        return -1;
    }
    cout << iter->first << endl;
    cout << iter->second->ts->num << endl;
    iter->second->_cl->show();

    return 0;
}