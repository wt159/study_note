#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <algorithm>

using std::endl;
using std::cout;

static std::map<int , int *> NumMap;
static int id = 0;

int funcId()
{
    NumMap[id] = new int(1);
    return id++;
}

struct Pam
{
    int num;
    Pam(){cout<<"pam 11"<<endl;}
    Pam(int num):num(num){
        cout<<"pam structure" << endl;
        }
    ~Pam() {cout << "pam dstructure " << num << endl;}
};
std::map<std::string, std::shared_ptr<Pam>> pamMap;
void testMap()
{
    std::string s1("1");
    pamMap.emplace(s1, std::make_shared<Pam>(1));
    std::string s2("2");
    pamMap.emplace(s2, std::make_shared<Pam>(2));
    std::string s3("3");
    pamMap.emplace(s3, std::make_shared<Pam>(3));
    for(auto it : pamMap)
        cout << "key:" << it.first << " value:" << it.second->num << endl;

    pamMap.erase("1");
    auto iter = pamMap.begin();
    pamMap.erase(iter);
}

void f1()
{
    std::map<int, Pam> mymap;
    {
    Pam nPam;
    std::shared_ptr<Pam> nPAm;
    nPAm->num = 1;
    for(int i=0; i<5; i++){
        nPam.num = i+1;
        mymap[i] = nPam;
    }
    }
    for(auto it : mymap) {
        std::cout << it.first << " " << it.second.num << std::endl;
    }

 
    auto print = [](const std::pair<int, Pam> &n)  
    { 
        std::cout << n.first <<  " " << n.second.num << std::endl; 
    };
 
    std::cout << "for_each and lmada:" << std::endl;
    std::for_each(mymap.begin(), mymap.end(), print);
    std::cout << '\n';
}

void printSet(const std::set<int> &temp)
{
    for(auto it : temp)
        std::cout << it << std::endl;
}

void f2()
{
    std::vector<int> ivec = {2,4,6,8,2,4,6,8};
    std::set<int> set2;
    set2.insert(ivec.cbegin(), ivec.cend());
    set2.insert({1,3,5,7,1,3,5,7});
    printSet(set2);
}

int main()
{
    // f2();
    testMap();
    while(1);
    return 0;
}