#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;

int& test_ref()
{
    static int temp = 0;
    temp++;
    return temp;
}
int* test_ptr()
{
    static int temp = 3;
    temp++;
    return &temp;
}
int main()
{
    cout << test_ref() << endl;
    cout << *test_ptr() << endl;
    return 0;
}