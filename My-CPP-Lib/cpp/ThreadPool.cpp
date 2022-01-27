#include "ThreadPool.h"
#include "MyLog.h"

namespace WTP
{
    ThreadPool::ThreadPool()
    {
        _config.coreThreadNum = 1;
        _config.maxThreadNum = 1;
        _config.cacheTimeout = PoolSeconds(2);
        init();
    }

    ThreadPool::ThreadPool(size_t coreThradNum, size_t maxThreadNum, size_t cacheTimeOutSecond)
    {
        _config.coreThreadNum = coreThradNum;
        _config.maxThreadNum = maxThreadNum;
        _config.cacheTimeout = PoolSeconds(cacheTimeOutSecond);
        init();
    }

    ThreadPool::ThreadPool(ThreadPoolConfig config)
        : _config(config)
    {
        init();
    }

    ThreadPool::~ThreadPool()
    {
        stop(true);
    }

    void ThreadPool::init()
    {
        _totalTaskNum.store(0);
        _waittingThreadNum.store(0);
        _isShutdown.store(false);
        _isShutdownNow.store(false);
        _isRunning.store(false);
        _coreWorkThread.clear();
        _cacheWorkThread.clear();

        if (isValidConfig(_config)) {
            _isAvailable.store(true);
        } else {
            _isAvailable.store(false);
        }
    }

    bool ThreadPool::isValidConfig(ThreadPoolConfig& config)
    {
        return !(config.coreThreadNum < 1 
                || config.coreThreadNum < config.maxThreadNum
                || config.cacheTimeout.count() < 1);
    }

    bool ThreadPool::start()
    {
        if(!_isAvailable.load() || _isRunning.load()) {
            return false;
        }

        for(size_t i=0; i<_config.coreThreadNum; i++) {
            addCoreThread();
        }
        for(size_t i=0; i<(_config.maxThreadNum-_config.coreThreadNum); i++) {
            addCacheThread();
        }
        _isRunning.store(true);
        return true;
    }

    bool ThreadPool::stop(bool isShutdownNow)
    {
        shutdown(isShutdownNow);
        return true;
    }

    void ThreadPool::threadloop(ThreadPool* obj, ThreadWrapperPtr threadPtr)
    {
        while (obj->_isRunning.load())
        {
            if (obj->_isShutdownNow.load()) {
                break;
            }

            if(threadPtr->state.load() != ThreadState::kRunning) {
                break;
            }

            ThreadPoolLock lock(obj->_taskLock);

            if (obj->_isShutdown.load() && obj->_tasks.size() == 0) {
                break;
            }

            if (obj->_tasks.size() == 0) {
                obj->_waittingThreadNum++;
                if(threadPtr->flag.load() == ThreadFlag::kCore) {
                    obj->_taskCV.wait(lock);
                }
                else if(threadPtr->flag.load() == ThreadFlag::kCache) {
                    auto state = obj->_taskCV.wait_for(lock, obj->_config.cacheTimeout);
                    if(state == std::cv_status::timeout) {
                        threadPtr->state.store(ThreadState::kStop);
                        obj->_waittingThreadNum--;
                        break;
                    }
                }
            }
            obj->_waittingThreadNum--;

            if (obj->_waittingThreadNum.load() == 0 && obj->_tasks.size() > obj->_config.coreThreadNum) {
                obj->addCacheThread();
            }

            auto task = obj->_tasks.front();
            obj->_tasks.pop();

            task();
        };
        return;
    }
    void ThreadPool::addCoreThread()
    {
        ThreadWrapperPtr ptr(new ThreadWrapper);

        _coreWorkThread.emplace_back(ptr);

        ptr->id.store((size_t)ptr.get());
        ptr->state.store(ThreadState::kRunning);
        ptr->flag.store(ThreadFlag::kCore);

        ThreadPtr thd(new std::thread(&ThreadPool::threadloop, this, ptr));
        ptr->ptr = thd;
    }
    void ThreadPool::addCacheThread()
    {
        auto iter = _cacheWorkThread.begin();
        for(; iter!=_cacheWorkThread.end();)
        {
            if((*iter)->state.load() == ThreadState::kStop) {
                if((*iter)->ptr->joinable()) {
                    (*iter)->ptr->join();
                }
                _cacheWorkThread.erase(iter);
            } else {
                iter++;
            }
        }

        ThreadWrapperPtr ptr(new ThreadWrapper);

        _cacheWorkThread.emplace_back(ptr);

        ptr->id.store((size_t)ptr.get());
        ptr->state.store(ThreadState::kRunning);
        ptr->flag.store(ThreadFlag::kCache);

        ThreadPtr thd(new std::thread(&ThreadPool::threadloop, this, ptr));
        ptr->ptr = thd;
    }

    void ThreadPool::shutdown(bool isShutdownNow)
    {
        _isShutdown.store(!isShutdownNow);
        _isShutdownNow.store(isShutdownNow);

        for (auto& temp : _coreWorkThread) {
            if(temp->ptr->joinable()) {
                temp->ptr->join();
            }
        }
        for (auto& temp : _cacheWorkThread) {
            if (temp->ptr->joinable()) {
                temp->ptr->join();
            }
        }

        _coreWorkThread.clear();
        _cacheWorkThread.clear();
    }
}