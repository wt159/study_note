// shared_ptr::get example
#include <iostream>
#include <map>
#include <memory>

struct testgroup {
    int* p;
    testgroup()
        : p(nullptr)
    {
        printf("group construct\n");
    }
    testgroup(int num)
        : p(nullptr)
    {
        printf("group construct\n");
        if(!p) {
            p = new int(num);
        }
    }
    ~testgroup()
    {
        if (p)
            delete p;
        p = nullptr;
        printf("group destruct\n");
    }
};
std::map<std::string, std::shared_ptr<testgroup>> _testmap;

void test1()
{
    int* p = new int(10);
    std::shared_ptr<int> a(p);

    if (a.get() == p)
        std::cout << "a and p point to the same location\n";

    // three ways of accessing the same address:
    std::cout << *a.get() << "\n";
    std::cout << *a << "\n";
    std::cout << *p << "\n";
}

void test2()
{
    std::string str("aaa");
    _testmap.emplace(str, std::make_shared<testgroup>());
    // int* ptr = (*(_testmap[str])).p;
    int** ptr = &(_testmap[str]->p);
    if (*ptr) {
        printf("shared_ptr not is nullptr\n");
    } else {
        printf("shared_ptr is nullptr\n");
        *ptr = new int(250);
    }

    // ptr = new int(520);
    // printf("ptr new int 520\n");

    if (*ptr) {
        printf("shared_ptr not is nullptr\n");
        printf("map shared_ptr struct is %d, ptr is %d\n",*(_testmap[str]->p), **ptr);
    } else {
        printf("shared_ptr is nullptr\n");
    }

    
}

void test3()
{
    std::string str("bbb");
    _testmap.emplace(str, std::make_shared<testgroup>());
    auto it = _testmap.find(str);
    if(it->second->p){
        printf("shared_ptr not is nullptr\n");
    } else {
        printf("shared_ptr is nullptr\n");
        it->second->p = new int(520);
    }

    if (it->second->p) {
        printf("shared_ptr not is nullptr\n");
        printf("map shared_ptr struct is %d\n",*(it->second->p));
    } else {
        printf("shared_ptr is nullptr\n");
    }
}

int main()
{
    test1();
    test2();
    test3();

    return 0;
}
