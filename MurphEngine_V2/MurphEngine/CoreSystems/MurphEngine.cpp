// MurphEngine.cpp : Defines the functions for the static library.
//
#include "MurphEngine.h"

#include <cassert>

#include "../LoggingSystem/Logging.h"
#include "../math/Vector.h"
#include "../Middleware/Bleach_New/BleachNew.h"
#include "GraphicsManager/GraphicsManager.h"
#include "XMLParser/WindowParser.h"



MurphEngine::MurphEngine()
{
    int error = SDL_Init(SDL_INIT_EVERYTHING);
    if (error != 0)
    {
        const std::string sdlError = SDL_GetError();
        LOG_TO_CONSOLE(kError, "SDL Initialization Error: " + sdlError);
        return;
    }
    m_graphicsManager.SetDefaultDrawColor(0, 0, 0, 255);
    WindowParser windowParser;
    windowParser.ParseWindowFile(&m_graphicsManager, "../MurphEngine/SystemConfig/WindowSetup.xml");
    LOG_TO_CONSOLE(kSystem, "Engine Initialized Successfully!");
}

MurphEngine::~MurphEngine()
{
    LOG_TO_CONSOLE(kSystem, "MurphEngine Instance Destroyed.");
}

/**
 * \brief Get Singleton instance of MurphEngine
 * \return Instance of MurphEngine
 */
MurphEngine* MurphEngine::GetInstance()
{
    if (s_pInstance == nullptr)
        s_pInstance = BLEACH_NEW(MurphEngine);
    return s_pInstance;
}

/**
 * \brief Shut down the MurphEngine instance
 */
void MurphEngine::ShutDown()
{
    LOG_TO_CONSOLE(kSystem, "MurphEngine Shutdown Initiating.");
    BLEACH_DELETE(s_pInstance);
}

/**
 * \brief Update Engine
 * \param deltaTime delta time
 * \return true if the engine is still running
 */
bool MurphEngine::Update(double deltaTime)
{
    bool isRunning = ProcessSDLEvents(); // this will only ring false if the player clicks the X button on the window.
    if (isRunning)
    {
        m_pInputManager.Update(deltaTime); // update input to have the latest key presses.
    	// render the current frame. (this is done before update because i was having issues with background not updating properly on scene switch.)
        Render();
        isRunning = m_sceneManager.Update(deltaTime); // delegate update to the scene manager.
    }
    return isRunning;
}

/**
 * \brief Process SDL Events like window close, key presses, etc.
 * \return false if engine should quit
 */
bool MurphEngine::ProcessSDLEvents() const
{
    return m_sceneManager.HandleSDLEvent();
}

/**
 * \brief Render the current frame
 */
void MurphEngine::Render() const
{
    m_graphicsManager.StartDrawingFrame(); // start drawing the frame.
    m_sceneManager.Render(); // delegate render to the scene manager.
    m_graphicsManager.PresentCurrentFrame(); // present the frame to the screen.
}
