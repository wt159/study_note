#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <cstring>
#include <map>
using namespace std;

struct NarrowLoad
{
    unsigned char x;
    unsigned long long y;
    unsigned long long z;
    friend bool operator==(NarrowLoad const &lhs, NarrowLoad const &rhs);
};
bool operator==(NarrowLoad const &lhs, NarrowLoad const &rhs)
{
    // return !memcmp(&lhs, &rhs, sizeof(NarrowLoad));
    return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
}

NarrowLoad global{ 'x', 12345ULL, 54321ULL};

bool g()
{
    NarrowLoad local{ 'x', 12345ULL, 54321ULL};

    return local==global;
}

int main()
{
    if(g()) {
        cout << "normal" << endl;
    } else {
        cout << "not normal" << endl;
    }
    return 0;
}