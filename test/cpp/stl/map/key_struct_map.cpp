#include <iostream>
#include <string>
#include <map>
using namespace std;
 
struct Info
{
    string name;
    int score;
 
    bool operator< (const Info &x) const
    {
        return this->score < x.score;
    }
};
 
int main()
{
    Info a, b;
 
    a.name = "eric";
    a.score = 90;
 
    b.name = "cat";
    b.score = 85;
 
    map<Info, int> m;
    m[a] = 1;
    m[b] = 2;
 
    map<Info, int>::iterator it;
    for(it = m.begin(); it != m.end(); it++)
    {
        cout << it->first.name << endl;
    }
 
    return 0;
}