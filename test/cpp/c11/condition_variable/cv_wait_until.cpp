#include <iostream>
#include <atomic>
#include <condition_variable>
#include <thread>
#include <chrono>
 
std::condition_variable cv;
std::mutex cv_m;
std::atomic<int> i{0};

using Ss = std::chrono::seconds;
using Ms = std::chrono::milliseconds;
using Us = std::chrono::microseconds;
 
void waits(int idx)
{
    std::unique_lock<std::mutex> lk(cv_m);
    auto now = std::chrono::system_clock::now();
    if(cv.wait_until(lk, now + idx*Ms(100), [](){return i == 1;}))
        std::cerr << "Thread " << idx << " finished waiting. i == " << i << '\n';
    else
        std::cerr << "Thread " << idx << " timed out. i == " << i << '\n';
}
 
void signals()
{
    std::this_thread::sleep_for(Ms(120));
    std::cerr << "Notifying...\n";
    cv.notify_all();
    std::this_thread::sleep_for(Ms(100));
    i = 1;
    std::cerr << "Notifying again...\n";
    cv.notify_all();
}
 
int main()
{
    std::thread t1(waits, 1), t2(waits, 2), t3(waits, 3), t4(signals);
    t1.join(); 
    t2.join();
    t3.join();
    t4.join();
}