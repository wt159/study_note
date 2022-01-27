#include <thread>
#include <chrono>

int main()
{
#if __cplusplus >= 201402L
    using namespace std::chrono_literals;
    auto interval = 10ms;//间隔
    std::this_thread::sleep_for(interval);
#endif // __cplusplus
    
    std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    std::this_thread::sleep_for(std::chrono::microseconds(1));
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::this_thread::sleep_for(std::chrono::minutes(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::hours(1));
    
    return 0;
}