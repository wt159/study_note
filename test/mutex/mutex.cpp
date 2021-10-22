#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include <mutex>

class MutexTest
{
private:
    std::recursive_mutex m_mutex;
public:
    MutexTest(/* args */){}
    ~MutexTest(){}
    void printa()
    {
        std::cout << __func__ << " befor" << std::endl;
        // std::unique_lock<std::recursive_mutex> lock(m_mutex);
        std::lock_guard<std::recursive_mutex> lock(m_mutex);
        std::cout << __func__ << " after" << std::endl;
    }
    void printb()
    {
        std::cout << __func__ << " befor" << std::endl;
        std::unique_lock<std::recursive_mutex> lock(m_mutex);
        std::lock_guard<std::recursive_mutex> lock(m_mutex);
        printa();
        std::cout << __func__ << " after" << std::endl;
    }
};

void testfunc()
{
    int counter = 0;
    std::mutex counter_mutex;
    std::vector<std::thread> threads;
 
    auto worker_task = [&](int id) {
        std::unique_lock<std::mutex> lock(counter_mutex);
        ++counter;
        std::cout << id << ", initial counter: " << counter << '\n';
        lock.unlock();
 
        // 我们模拟昂贵操作时不保有锁
        std::this_thread::sleep_for(std::chrono::seconds(1));
 
        lock.lock();
        ++counter;
        std::cout << id << ", final counter: " << counter << '\n';
    };
 
    for (int i = 0; i < 10; ++i) threads.emplace_back(worker_task, i);
 
    getchar();
    for (auto &thread : threads) thread.detach();

    std::this_thread::sleep_for(std::chrono::seconds(11));
}
void test2func()
{
    MutexTest test;
    test.printb();
}
 
int main()
{
    test2func();
}