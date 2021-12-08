#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;

class MyClass
{
public:
    // MyClass() {
    //     cout << "MyClass()" << endl;
    // }
    MyClass(int capacity = 1) {
        _capacity = capacity;
        cout << "MyClass(int capacity)" << endl;
    }
    MyClass(MyClass &&) {
        cout << "MyClass(MyClass &&)" << endl;
    }
    MyClass(const MyClass &) {
        cout << "MyClass(const MyClass &)" << endl;
    }
    MyClass &operator=(MyClass &&) {
        cout << "MyClass &operator=(MyClass &&)" << endl;
        return *this;
    }
    MyClass &operator=(const MyClass &) {
        cout << "MyClass &operator=(const MyClass &)" << endl;
        return *this;
    }
    ~MyClass() {
        cout << "capacity: " << _capacity << " ~MyClass()" << endl;
    }

private:
    int _capacity = 0; 
};


int main()
{
    cout << "1" << endl;
    std::map<int, MyClass> myClassesMap;
    cout << "2" << endl;
    cout << "3" << endl;
    for (int i = 0; i < 3; i++)
    {
        myClassesMap[i];
        // myClassesMap.emplace(i, MyClass(i));
    }
    cout << "4" << endl;
    return 0;
}