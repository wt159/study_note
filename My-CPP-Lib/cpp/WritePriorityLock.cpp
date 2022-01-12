#include <WritePriorityLock.h>

namespace WTP
{
    WritePriorityLock::WritePriorityLock() { }
    WritePriorityLock::~WritePriorityLock() { }

    void WritePriorityLock::readLock()
    {
		std::unique_lock<Mutex> lock(_mutex);
        _readCount++;
        _writeCndVar.wait(lock, [this]{ return _isWriting.load(); });
    }
    void WritePriorityLock::readUnlock()
    {
        _readCount--; 
        
    }

    void WritePriorityLock::writeLock()
    {
        _writeCount++;
    }
    void WritePriorityLock::writeUnlock()
    {
        _writeCount--;
    }
}