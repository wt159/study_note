#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <future>

class Work
{
public:
    Work() : _value(42) {}
    Work(Work &&) = default;
    Work(const Work &) = default;
    Work &operator=(Work &&) = default;
    Work &operator=(const Work &) = default;
    ~Work() {}

    std::future<int> spawn()
    {
        return std::async([=, tmp = *this] () -> int { return tmp._value;} );
    }

private:
    int _value; 
};

std::future<int> test()
{
    Work temp;
    return temp.spawn();
}

int main()
{
    using namespace std;
    future<int> f = test();
    f.wait();
    cout << "future value is " << f.get() << endl;
    return 0;
}