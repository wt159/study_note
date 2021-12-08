#pragma once

#include <iomanip>
#include <ctime>
#include <chrono>


/**
 * C++11
  */
uint64_t getSysTimeOnMilliSecond()
{
    auto time = std::chrono::high_resolution_clock::now();
    auto then = std::chrono::time_point_cast<std::chrono::milliseconds>(time);
    uint64_t result = 
    return result;
}