#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <memory>
#include <map>
using namespace std;



class Deleter
{
public:
    void operator() (int* p)
    {
        cout << "delete p, *p=" << *p << endl;
        delete p;
        p = nullptr;
    }
};

auto FuncDeleter = [](int *p) 
{ 
    cout << "delete p, *p=" << *p << endl;
    delete p; 
    p = nullptr; 
    

};
typedef void(*delType)(int *);

void test()
{
    std::shared_ptr<int> s1(new int(1), FuncDeleter);
    Deleter del;
    std::shared_ptr<int> s2(new int(3), del);

    std::unique_ptr<int, decltype(FuncDeleter)> u1(new int(4), FuncDeleter);
    std::unique_ptr<int, delType> u2(new int(5), FuncDeleter);
    std::unique_ptr<int, Deleter> u3(new int(6));
}




int main()
{
    test();
    return 0;
}