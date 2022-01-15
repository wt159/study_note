#include <WritePriorityLock.h>

namespace WTP
{
    WritePriorityLock::WritePriorityLock() { }
    WritePriorityLock::~WritePriorityLock() { }

    void WritePriorityLock::readLock()
    {
        std::unique_lock<Mutex> lock(_mutex);
        _readCndVar.wait(lock, [&] { return 0 == _writeCount; });
        _readCount++;
    }
    void WritePriorityLock::readUnlock()
    {
        std::unique_lock<Mutex> lock(_mutex);
        if( --_readCount == 0 && _writeCount == 1)
        {
            _writeCndVar.notify_one();
        }
    }

    void WritePriorityLock::writeLock()
    {
        std::unique_lock<Mutex> lock(_mutex);
        _writeCount++;
        _writeCndVar.wait(lock, [&]{ return (0 == _readCount) && (0 == _writeCount);});
    }
    void WritePriorityLock::writeUnlock()
    {
        std::unique_lock<Mutex> lock(_mutex);
        if(--_writeCount != 0) {
            _writeCndVar.notify_one();
        } else {
            _readCndVar.notify_one();
        }
    }
}