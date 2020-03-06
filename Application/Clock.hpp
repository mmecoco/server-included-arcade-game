#pragma once

#include <chrono>
#include <ctime>
#include <math.h>

#include <iostream>

class Clock
{
private:
    std::chrono::system_clock::time_point m_start;
    void startClock() { m_start = std::chrono::system_clock::now(); };
public:
    Clock() { startClock(); };
    ~Clock() = default;
    std::chrono::duration<double_t, std::milli> getClock(void) { return std::chrono::system_clock::now() - m_start; };
    void restart() { startClock(); }
};