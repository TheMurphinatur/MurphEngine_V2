#include "Application.h"

#include "../MurphEngine.h"
#include "../LoggingSystem/Logging.h"


#define FPS_LOGGING 1

/**
 * \brief Initialize Application and get our engine instance.
 */
Application::Application()
	: m_pEngine(MurphEngine::GetInstance())
{
}

/**
 * \brief Shut down application and clean up our engine instance.
 */
Application::~Application() = default;

bool Application::Update(double deltaTime)
{
    m_pEngine->GetTimeManager()->StartFrameTimer();

    static int frameCount;
    static double frameTime;

#if FPS_LOGGING
    ++frameCount;
    frameTime += deltaTime;
    if (frameTime >= 1000)
    {
        LOG_TO_CONSOLE(kDebug, "FPS: " + std::to_string(frameCount));
        frameCount = 0;
        frameTime = -1000;
    }
#endif
    return m_pEngine->Update(deltaTime);
}

