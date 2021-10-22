#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;

void test_r_value()
{
    int i = 24;
    int &r1 = i;
    const int &r2 = 23;
    // int &r2 = 23;
    // int &&r2 = r1;
    // int &r3 = i *23;
    int && r4 = i *2;
    int&& r5 = 2;
    printf("i:%d, r1:%d, r4:%d,r5:%d\n", i, r1, r4, r5);
    printf("&i:%p, &r1:%p, &r4:%p, &r5:%p\n", &i, &r1, &r4, &r5);
}


int main()
{
    test_r_value();
    return 0;
}