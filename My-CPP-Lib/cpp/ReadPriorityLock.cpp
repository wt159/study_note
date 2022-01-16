#include "ReadPriorityLock.h"

namespace WTP
{
    ReadPriorityLock::ReadPriorityLock() : _readCount(0) { }

    ReadPriorityLock::~ReadPriorityLock()
    {
        readUnlock();
    }

    void ReadPriorityLock::readLock()
    {
        _readCount++;
        if(_readCount.load() == 1) {
            _mutex.lock();
        }
    }

    void ReadPriorityLock::readUnlock()
    {
        _readCount--;
        if(_readCount.load() == 0) {
            _mutex.unlock();
        }
    }

    void ReadPriorityLock::writeLock()
    {
        _mutex.lock();
    }

    void ReadPriorityLock::writeUnlock()
    {
        _mutex.unlock();
    }
}