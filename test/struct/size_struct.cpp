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

struct SizeStruct {
public:
    ~SizeStruct() {}
};


int main()
{
    if(g()) {
        cout << "normal" << endl;
    } else {
        cout << "not normal" << endl;
    }

    SizeStruct s;
    SizeStruct * sizeptr = new SizeStruct();

    cout << "size:" << sizeof(SizeStruct) << endl;
    cout << "size:" << sizeof s << endl;
    cout << "size:" << sizeof(*sizeptr) << endl;

    delete sizeptr;
    return 0;
}