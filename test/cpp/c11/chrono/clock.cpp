#include <iostream>
#include <thread>
#include "clock.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif // _WIND32

// 获取系统的当前时间，单位微秒(us)
int64_t GetSysTimeMicros()
{
#ifdef _WIN32
// 从1601年1月1日0:0:0:000到1970年1月1日0:0:0:000的时间(单位100ns)
#define EPOCHFILETIME (116444736000000000UL)
    FILETIME ft;
    LARGE_INTEGER li;
    int64_t tt = 0;
    GetSystemTimeAsFileTime(&ft);
    li.LowPart = ft.dwLowDateTime;
    li.HighPart = ft.dwHighDateTime;
    // 从1970年1月1日0:0:0:000到现在的微秒数(UTC时间)
    tt = (li.QuadPart - EPOCHFILETIME) / 10;
    return tt;
#else
    timeval tv;
    gettimeofday(&tv, 0);
    return (int64_t)tv.tv_sec * 1000000 + (int64_t)tv.tv_usec;
#endif // _WIN32
    return 0;
}

// 函数 f() 做一些耗时工作
void f()
{
    volatile double d = 0;
    for (int n = 0; n < 1000; ++n)
        for (int m = 0; m < 1000; ++m)
            d += d * n * 1;
}

int main()
{
    uint64_t u_start = GetSysTimeMicros();
    std::clock_t c_start = std::clock();
    auto t_start = std::chrono::high_resolution_clock::now();
    std::thread t1(f);
    std::thread t2(f); // 在二个线程上调用 f()
    t1.join();
    t2.join();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    uint64_t u_end = GetSysTimeMicros();
    std::clock_t c_end = std::clock();
    auto t_end = std::chrono::high_resolution_clock::now();

    printf("file name: %s, function name = %s, current line:%d Date:%s Timer:%s\n",
           __FILE__, __FUNCTION__, __LINE__, __DATE__, __TIME__);

    std::cout << "Wall clock time passed: "
              << u_end - u_start << "us\n"
              << std::fixed << std::setprecision(2) << "CPU time used: "
              << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n"
              << "clock sizeof:" << sizeof(c_start) << " :" << sizeof(int) << "\n"
              << "Wall clock time passed: "
              << std::chrono::duration<double, std::milli>(t_end - t_start).count()
              << " ms\n"
              << std::chrono::duration<double, std::micro>(t_end - t_start).count()
              << " us\n"
              << std::chrono::duration<double, std::nano>(t_end - t_start).count()
              << " ns\n"
              << std::chrono::duration<double, std::pico>(t_end - t_start).count()
              << " ns/1000\n";
}