#pragma once

#include <Mutex.h>
#include <atomic>
#include <NoCopy.h>

namespace WTP
{

    class WritePriorityLock : NoCopy
    {
    public:
        WritePriorityLock();
        ~WritePriorityLock();

        void readLock();
        void readUnlock();

        void writeLock();
        void writeUnlock();
    private:
        std::atomic<int> _writeCount = 0;
        std::atomic<int> _readCount = 0;
        Mutex _mutex;
        std::atomic<bool> _isReadLocking = false;
    };

}