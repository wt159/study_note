#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
using namespace std;

typedef pair<int, int> pair_int;

int main()
{
    pair_int p(1, 2);
    std::set<pair<int, int>> a;
    // unordered_set<decltype(p), int> b;  //error

    cout << a.size() << endl;
    // cout << b.size() << endl;

    return 0;
}