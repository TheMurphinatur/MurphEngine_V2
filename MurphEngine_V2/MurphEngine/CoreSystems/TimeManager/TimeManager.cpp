#include "TimeManager.h"

#include "../LoggingSystem/Logging.h"

/**
 * \brief initialize time manager and start engine timer
 */
TimeManager::TimeManager()
{
    StartEngineTimer();
}

/**
 * \brief Shut down time manager and report how long the engine was running.
 */
TimeManager::~TimeManager()
{
    LOG_TO_CONSOLE(kSystem, "System was running for " + std::to_string(GetEngineUpTimeSeconds()) +  " seconds.");
}


/**
 * \brief Start a timer that will be used to calculate the length of time the engine ran at shutdown.
 */
void TimeManager::StartEngineTimer()
{
    m_engineStart = HighResolutionClock::now();
}

/**
 * \brief Start individual frame timer
 */
void TimeManager::StartFrameTimer()
{
    m_frameTimer = HighResolutionClock::now();
}

/**
 * \brief Get the time since Frame Timer started in milliseconds
 * \return delta time in milliseconds
 */
double TimeManager::GetDeltaTimeMs() const
{
    using namespace std::chrono;

    const TimePoint currentTime = HighResolutionClock::now();
    auto timeSpan = duration_cast<duration<double, std::milli>>(currentTime - m_frameTimer);

    return timeSpan.count();
}

/**
 * \brief Get the time since Frame Timer started in seconds
 * \return delta time in seconds
 */
double TimeManager::GetDeltaTimeSeconds() const
{
    using namespace std::chrono;
    const TimePoint currentTime = HighResolutionClock::now();
    auto timeSpan = duration_cast<duration<double>>(currentTime - m_frameTimer);

    return timeSpan.count();
}

/**
 * \brief Get Length of time Engine has been running in seconds.
 * \return Length of time engine was running in seconds
 */
double TimeManager::GetEngineUpTimeSeconds() const
{
    using namespace std::chrono;
    const TimePoint currentTime = HighResolutionClock::now();
    auto lifeSpan = duration_cast<duration<double>>(currentTime - m_engineStart);

    return lifeSpan.count();
}
