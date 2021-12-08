#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <memory>
using namespace std;


template <typename T>
class NewTemplate
{
private:
    T* _template;
public:
    NewTemplate(){
        cout << "NewTemplate()" << endl;
    }

    NewTemplate(const T* temp) : _template(temp)
    {
        cout << "NewTemplate(const T* temp)" << endl;
    }
    ~NewTemplate(){
        cout << "~NewTemplate()" << endl;
    }
};

typedef NewTemplate<int> NewTemplateInt;

int main()
{
    NewTemplateInt *ptr = new NewTemplateInt();
    std::shared_ptr<NewTemplateInt> ntPtr(ptr);
    std::map<int, NewTemplateInt*> tempMap;
    tempMap[0];
    return 0;
}