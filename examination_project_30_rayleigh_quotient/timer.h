#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
private:
    std::chrono::high_resolution_clock::time_point startTime;

public:
    Timer();

    void start();

    // Returns elapsed time in seconds
    double stop();
};

#endif