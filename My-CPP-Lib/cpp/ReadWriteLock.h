#pragma once

#include <Mutex.h>
#include <NoCopy.h>
#include <atomic>

namespace WTP
{
    enum class RWPriority { kReadPriority = 0, kWritePriority, kReadWriteEquity };

    class ReadWriteLock : NoCopy
    {
    public:
        ReadWriteLock( RWPriority priority);
        ~ReadWriteLock();
    
    private:
        RWPriority _priority;
    };
}