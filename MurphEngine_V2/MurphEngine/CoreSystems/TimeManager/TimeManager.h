#pragma once
#include <chrono>


class TimeManager
{
    using HighResolutionClock = std::chrono::high_resolution_clock;
    using TimePoint = HighResolutionClock::time_point;

    TimePoint m_engineStart;

    TimePoint m_startTime;
    TimePoint m_frameTimer;

public:
    TimeManager();
    ~TimeManager();


    void StartFrameTimer();

    double GetDeltaTimeMs() const;
    double GetDeltaTimeSeconds() const;

private:
    void StartEngineTimer();
    double GetEngineUpTimeSeconds() const;
};