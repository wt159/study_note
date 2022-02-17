#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;

struct TestStruct {
    int a;
    int b;
    int c[5];
};

struct Test {
    std::map<int, TestStruct> mymap;
};

int main()
{
    Test a;
    cout << a.mymap[0].c[1]  << endl;
    return 0;
}