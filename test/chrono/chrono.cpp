#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
using namespace std;


int main()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::this_thread::sleep_for(std::chrono::microseconds(1));
    std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}