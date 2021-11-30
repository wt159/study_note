#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <memory>
#include <map>
using namespace std;


int main()
{
    std::shared_ptr<char> ptr(new char[10]);
    return 0;
}