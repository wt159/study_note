#include <iostream>
#include <string>
#include <list>
#include <memory>
#include <vector>
#include <map>
using namespace std;

void* create(int num)
{
    int *p = new int(num);
    cout << __func__ << " " <<  p << endl;
    return p;
}

void print(void *p)
{
    cout << __func__ << " " <<  p << endl;
    int *d = (int *)p;
    if(d != NULL)
        cout << __func__ << " " << *d << endl;
}

void destory(void *p)
{
    #if 0
    if(*p != NULL) {
        delete *p;
    }
    #else
    cout << __func__ << " " <<  p << endl;
    if(p != NULL) {
        delete p;
    }
    #endif
    //*p = NULL;
}

int main()
{
    void *p = create(50);
    print(p);
    destory(p);
    print(p);
    return 0;
}