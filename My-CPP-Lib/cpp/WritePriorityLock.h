#pragma once

#include <Mutex.h>
#include <atomic>
#include <NoCopy.h>
#include <condition_variable>

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
        size_t _writeCount = 0;
        size_t _readCount = 0;
        Mutex _mutex;
        bool _isWriting = false;
        std::condition_variable _readCndVar;
        std::condition_variable _writeCndVar;
    };

}