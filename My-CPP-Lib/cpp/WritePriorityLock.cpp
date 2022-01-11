#include <WritePriorityLock.h>

namespace WTP
{
    WritePriorityLock::WritePriorityLock() { }
    WritePriorityLock::~WritePriorityLock() { }

    void WritePriorityLock::readLock()
    {
        _readCount++;
        if(_writeCount.load() > 0) {
            _isReadLocking.store(true);
            _mutex.lock();
        }
    }
    void WritePriorityLock::readUnlock()
    {
        _readCount--; 
        // fixme 
        // if(_isReadLocking.load()) {
        //     _mutex.unlock();
        // }
    }

    void WritePriorityLock::writeLock()
    {
        _writeCount++;
        _mutex.lock();
    }
    void WritePriorityLock::writeUnlock()
    {
        _writeCount--;
        _mutex.unlock();
    }
}