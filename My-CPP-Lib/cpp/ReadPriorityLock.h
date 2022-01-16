#pragma once
#include "Mutex.h"
#include "NoCopy.h"
#include <atomic>

namespace WTP
{
    class ReadPriorityLock : NoCopy
    {
    public:
        ReadPriorityLock();
        ~ReadPriorityLock();

        void readLock();
        void readUnlock();

        void writeLock();
        void writeUnlock();
    private:
        std::atomic<int> _readCount;
        Mutex _mutex;
    };
}