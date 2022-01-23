#pragma once

#include "NoCopy.h"
#include <thread>
#include <list>
#include <functional>
#include <atomic>
#include <chrono>
#include <memory>
#include <mutex>
#include <queue>
#include <condition_variable>

namespace WTP
{
    enum class ThreadState { kInit = 0, kWaitting, kRunning, kStop };

    enum class ThreadFlag { kInit = 0, kCore, kCache };

    typedef std::chrono::seconds PoolSeconds;

    struct ThreadPoolConfig
    {
        size_t coreThreadNum;
        size_t maxThreadNum;
        size_t maxTaskSize;
        PoolSeconds cacheTimeout;
    };

    typedef std::function<void(void)> TaskFuncPtr;

    typedef std::shared_ptr<std::thread> ThreadPtr;
    typedef std::atomic<size_t>            ThreadID;
    typedef std::atomic<ThreadState>    ThreadStateAtomic;
    typedef std::atomic<ThreadFlag>     ThreadFlagAtomic;

    struct ThreadWrapper
    {
        ThreadPtr ptr;
        ThreadID id;
        ThreadStateAtomic state;
        ThreadFlagAtomic flag;

        ThreadWrapper()
            : ptr(nullptr)
            , id(0)
            , state(ThreadState::kInit)
            , flag(ThreadFlag::kInit)
        {}
    };

    typedef std::shared_ptr<ThreadWrapper> ThreadWrapperPtr;
    typedef std::unique_lock<std::mutex> ThreadPoolLock;
    
    class ThreadPool : NoCopy
    {
    public:
        ThreadPool();
        ThreadPool(size_t coreThradNum, size_t maxThreadNum, size_t cacheTimeOutSecond);
        ThreadPool(ThreadPoolConfig config);
        ~ThreadPool();

        bool start();
        bool stop(bool isShutdownNow);

        template<typename T, typename F, typename ...ARG>
        bool runTask(T obj, F f, ARG ...args)
        {
            if(!_isAvailable || !_isRunning || _isShutdownNow || _isShutdown) {
                return false;
            }
            TaskFuncPtr task = std::bind(f, std::mem_fn(obj), args...);

            ThreadPoolLock lock(_taskLock);
            _taskList.push(task);
            lock.unlock();
            
            _taskCV.notify_one();
        }

        /* thread pool status */
        size_t getWaitThreadNum();
    
    private:
        static void threadloop(ThreadPool* obj, ThreadWrapperPtr threadPtr);
        bool isValidConfig(ThreadPoolConfig& config);
        void addCoreThread();
        void addCacheThread();

        void shutdown(bool isShutdownNow);

    private:
        ThreadPoolConfig _config;

        std::list<ThreadWrapperPtr> _coreWorkThread;

        std::list<ThreadWrapperPtr> _cacheWorkThread;
        std::mutex _cacheThreadMutex;
        std::condition_variable _cacheThreadCV;

        std::queue<TaskFuncPtr> _taskList;

        std::mutex _taskLock;
        std::condition_variable _taskCV;

        std::atomic<size_t> _totalTaskNum;
        std::atomic<size_t> _waittingThreadNum;
        ThreadID    _threadID;
        
        std::atomic<bool> _isShutdown;
        std::atomic<bool> _isShutdownNow;
        std::atomic<bool> _isAvailable;
        std::atomic<bool> _isRunning;
    };
    
}