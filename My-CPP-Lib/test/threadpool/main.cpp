#include <iostream>
#include <ThreadPool.h>

void pool_test(int i)
{ 
    std::cout << __func__ << " " << i << std::endl;
}

int main(int, char**) {
    std::cout << "Hello, world!\n";
    WTP::ThreadPool pool;
    pool.start();
    for(int i=0; i<10; i++) {
        pool.runTask(pool_test, i);
    }
}
