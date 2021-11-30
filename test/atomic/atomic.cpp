#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <atomic>
#include <map>

using namespace std;

template <typename T>
struct Atomic{
    volatile T var;
};

int main()
{
    Atomic<int> a;
    a.var = 10;

    std::atomic<int> b;
    b.store(11);
    
    cout << "my atomic:" << a.var << endl;
    cout << "std atomic:" << b.load() << endl;
    return 0;
}