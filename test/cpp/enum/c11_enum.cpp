#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;

enum OldEnumA
{
    OldEnumA_a = 0,
    OldEnumA_b,
};

enum OldEnumB
{
    OldEnumB_a,
    OldEnumB_b,
};

enum class NewEnumA { NewEnumA_a = 0, NewEnumA_b };
enum class NewEnumB { NewEnumB_a = 0, NewEnumB_b };

int main()
{
    if(OldEnumA_a == OldEnumB_a) //Wran : 比较两个不同枚举类型的枚举变量
    {
        cout << "OldEnumA_a == OldEnumB_a" << endl;
    }
    else
    {
        cout << "OldEnumA_a != OldEnumB_a" << endl;
    }

    // if(NewEnumA_a == NewEnumB_a) //Error : NewEnumA_a 未定义标识符
    // if(NewEnumA::NewEnumA_a == NewEnumB::NewEnumB_a) //Error : 操作符不匹配
    if(0)
    {
        cout << "NewEnumA_a == NewEnumB_a" << endl;
    }
    else
    {
        cout << "NewEnumA_a != NewEnumB_a" << endl;
    }

    return 0;
}