#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <memory>
#include <thread>
#include <queue>
#include <functional>
using namespace std;

typedef struct
{
    int a;
    int b;
    int c;
}TestNumStruct;

typedef std::shared_ptr<TestNumStruct> TestNumStructPtr;

std::queue<TestNumStructPtr> TestQueue;

void test(TestNumStructPtr& data)
{
    cout << "func ref count: " << data.use_count() << endl;
    data = TestQueue.front();
    TestQueue.pop();
}

int main()
{
    TestNumStructPtr data = std::make_shared<TestNumStruct>();
    cout << "count: " << data.use_count() << endl;

    TestNumStructPtr& temp1 = data;
    cout << "ref count: " << data.use_count() << endl;

    TestNumStructPtr temp2 = data;
    cout << "copy count: " << data.use_count() << endl;

    auto f = std::bind(test, temp1);
    cout << "bind ref count: " << data.use_count() << endl;

    // TestQueue.push(data);
    TestQueue.emplace(temp1);
    cout << "queue count: " << data.use_count() << endl;
    test(temp1);

    return 0;
}