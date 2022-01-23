#include <iostream>
#include <ThreadPool.h>

class TestPool
{
public:
    void test_print(int i)
    {
        std::cout << __func__ << " " << i << std::endl;
    }
};

void pool_test(int i)
{ 
    std::cout << __func__ << " " << i << std::endl;
}

int main(int, char**) {
    std::cout << "Hello, world!\n";
    WTP::ThreadPool pool;
    TestPool test;

    std::cout << "start\n";
    pool.start();
    for(int i=0; i<10; i++) {
        pool.runTask(pool_test, i);
        pool.runTaskWithObj(&test, TestPool::test_print, i);
    }

    std::cout << "stop\n";
    pool.stop(false);
}
