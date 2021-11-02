#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;

void fcn3()
{
    int v1 = 42;
    // auto f = [v1] ()  { return ++v1; };
    auto f = [v1]() mutable
    { return ++v1; }; //错误
    v1 = 0;
    auto j = f();
}

void test(bool *sta)
{
    *sta = true;
}

int main()
{
    bool stb = false;
    test(&stb);
    std::cout << "state:" << (stb ? "true" : "false") << std::endl;
    return 0;
}