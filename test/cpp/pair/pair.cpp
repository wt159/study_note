#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include "C++/myBasicModule/ThreadSafeMap.hpp"

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
};


using newPairType = std::pair<TestStruct, B *>;


int main()
{
    
    return 0;
}