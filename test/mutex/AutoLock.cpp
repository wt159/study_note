#include <iostream>
#include <thread>
#include <mutex>

class NoCopyAble
{
public:
    NoCopyAble() = default;
    NoCopyAble(NoCopyAble&) = delete;
    NoCopyAble(NoCopyAble&&) = delete;
    void operator=(NoCopyAble&) = delete;
    void operator=(NoCopyAble&&) = delete;
    virtual ~NoCopyAble() = default;
};

class AutoLock : public NoCopyAble
{
public:
    AutoLock() = delete;

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

class SmartLock : public NoCopyAble
{
public:
    SmartLock() = delete;

    SmartLock(std::mutex& lock)
        : _lock(lock)
        , _isLock(false)
    {
       this->lock();
    }
    ~SmartLock()
    {
        this->unlock();
    }
    void lock()
    {
        if(!_isLock) {
            _lock.lock();
            _isLock = true;
        }
    }
    void unlock()
    {
        if(_isLock) {
            _lock.unlock();
            _isLock = false;
        }
    }

private:
    std::mutex& _lock;
    bool _isLock;
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
    std::cout << "1" << std::endl;
    std::mutex mutex;
    AutoLock lock(mutex);
    // AutoLock lock2(lock);  //Error
    // AutoLock lock3 = lock;  //Error  //Error
    // AutoLock lock4(std::move(lock));  //Error

    // AutoLock lock5 = lock;
    std::cout << "2" << std::endl;
    AutoLock& lock6 = lock;
    std::cout << "3" << std::endl;
    AutoLock& lock7 = lock6;
    std::cout << "4" << std::endl;
    std::mutex smutex;
    SmartLock locks1(smutex);
    std::cout << "5" << std::endl;
    locks1.unlock();
    std::cout << "6" << std::endl;
    // SmartLock locks2(locks1);  //Error
    // SmartLock locks3 = locks1;  //Error
    return 0;
}