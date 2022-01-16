#pragma once

#include <mutex>

/**
 * mutex                    Mutex class (class )
 * recursive_mutex          Recursive mutex class (class )
 * timed_mutex              Timed mutex class (class )
 * recursive_timed_mutex    Recursive timed mutex (class )
 */

namespace WTP
{

// class Mutex
// {
// public:
//     Mutex() = default;
//     Mutex(Mutex &&) = default;
//     Mutex(const Mutex &) = default;
//     Mutex &operator=(Mutex &&) = default;
//     Mutex &operator=(const Mutex &) = default;
//     ~Mutex() = default;

// private:
//     std::recursive_mutex _mutex;
// };

// typedef std::recursive_mutex Mutex;
typedef std::mutex Mutex;

}