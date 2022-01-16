#pragma once

#include "NoCopy.h"
#include <thread>
#include <list>
#include <functional>
#include <atomic>
#include <chrono>
#include <memory>
#include <mutex>
#include <condition_variable>

namespace WTP
{
    enum class TaskPriorityLevel { kHighPriority = 0, kNormalPriority };
    
    enum class ThreadState { kInit = 0, kWaitting, kRunning, kStop };

    enum class ThreadFlag { kInit = 0, kCore, kCache };

    typedef std::chrono::seconds PoolSeconds;

    struct ThreadPoolConfig
    {
        int coreThreadNum;
        int cacheThreadNum;
        PoolSeconds timeout;
    };

    typedef std::shared_ptr<std::function<void(void)>> TaskFuncPtr;

    typedef std::shared_ptr<std::thread> ThreadPtr;
    typedef std::atomic<int>            ThreadID;
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
        ThreadPool(ThreadPoolConfig config);
        ~ThreadPool();

        bool start();
        bool stop();

        template<typename T, typename F, typename ...ARG>
        void runTask(TaskPriorityLevel level, T obj, F f, ARG ...args)
        {

        }
    
    private:
    
    private:
        ThreadWrapperPtr _threadManager;
        std::list<ThreadWrapperPtr> _coreWorkThread;
        std::list<ThreadWrapperPtr> _cacheWorkThread;

        std::list<TaskFuncPtr> _highPriorityTaskList;
        std::list<TaskFuncPtr> _normalPriorityTaskList;

        std::mutex _taskLock;
        std::condition_variable _taskCV;
        
        ThreadPoolConfig config;
    };
    
}