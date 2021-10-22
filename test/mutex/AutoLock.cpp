#include <iostream>
#include <thread>
#include <mutex>

class AutoLock
{
public:
    AutoLock() = delete;
    AutoLock(AutoLock&) = delete;
    AutoLock(AutoLock&&) = delete;
    // void operator=(AutoLock) = delete;
    // AutoLock& operator=(AutoLock) = delete;

    AutoLock(std::mutex& lock)
        :_lock(lock)
    {
        _lock.lock();
    }
    ~AutoLock()
    {
        _lock.unlock();
    }
private:
    std::mutex& _lock;
};

class Test
{
public:
    Test() = default;
    ~Test() = default;
    void print()
    {
        AutoLock lock(_mutex);
        std::cout << "test lock" << std::endl;
    }
private:
    std::mutex _mutex;
};


int main(int argc, char const *argv[])
{
    std::mutex mutex;
    AutoLock lock(mutex);
    // AutoLock lock2(lock);
    // AutoLock lock3 = lock;
    // AutoLock lock4(std::move(lock));

    AutoLock lock5 = lock;
    AutoLock& lock6 = lock;
    AutoLock& lock7 = lock6;

    // std::thread thread[5];
    // for(int i=0; i<5; i++)
    // {
    //     thread[i].
    // }
    return 0;
}