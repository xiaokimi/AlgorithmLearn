#pragma once

#include <chrono>
#include <ctime>
#include <iostream>

#ifndef WIN32
#define WIN32
#endif

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
    void GetTimeDate()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);

        std::tm local_time;
        #ifdef WIN32
        localtime_s(&local_time, &now_time);
        #else
        localtime_r(&now_time, &localtime);
        #endif

        int year = local_time.tm_year + 1900;
        int month = local_time.tm_mon + 1;
        int day = local_time.tm_mday;
    }

private:
    std::chrono::system_clock::time_point mCurrent;
};