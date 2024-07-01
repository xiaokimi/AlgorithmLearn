#pragma once

#include <chrono>
#include <iostream>

class Timer
{
public:
    Timer()
    {
        mCurrent = std::chrono::system_clock::now();
    }

    ~Timer()
    {
        std::chrono::system_clock::time_point cur = std::chrono::system_clock::now();
        std::chrono::system_clock::duration elapsed = cur - mCurrent;
        long long elapsed_microseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << "------------ : " << elapsed_microseconds << std::endl;
    }

private:
    std::chrono::system_clock::time_point mCurrent;
};