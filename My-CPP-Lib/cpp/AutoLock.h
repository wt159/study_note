#pragma once

#include <Mutex.h>
#include <NoCopy.h>
#include <atomic>

namespace WTP
{

class AutoLock : NoCopy
{
public:
    AutoLock() : _mutex(), _isLock(true)
    {
        _mutex.lock();
    }
    ~AutoLock()
    {
        unlock();
    }

    void lock()
    {
        if(!_isLock.load()) {
            _mutex.lock();
        }
    }
    void unlock()
    {
        if(_isLock.load()) {
            _mutex.unlock();
            _isLock.store(false);
        }
    }
private:
    Mutex _mutex;
    std::atomic<bool> _isLock;
};

}