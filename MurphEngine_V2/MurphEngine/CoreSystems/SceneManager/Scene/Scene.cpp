#include "Scene.h"

#include "../../../LoggingSystem/Logging.h"
#include "Bleach_New/BleachNew.h"
#include "../../../../DemoProject/GameApplication/GameParser/GameLevelParser.h"

//Scene::Scene(const char* sceneXMLPath)
//	: m_engine(MurphEngine::GetInstance())
//	, m_backgroundTexture(nullptr)
//{
//	m_sceneXMLPath = sceneXMLPath;
//}

void Scene::Initialize()
{
	if (m_sceneXMLPath != nullptr)
	{
        m_engine = MurphEngine::GetInstance();
        GameLevelParser parser(&m_sceneEntityManager);
        parser.ParseFile(m_sceneXMLPath);
        m_hasBeenInitialized = true;
	}
    LOG_TO_CONSOLE(kSystem, "Scene Initialized");
}

void Scene::ChangeScene(const std::string& sceneName)
{
    LOG_TO_CONSOLE(kDebug, "Scene Change!");
}

bool Scene::Update(double deltaTime)
{
    m_sceneEntityManager.Update(deltaTime);
    return m_canContinueLoop;
}

bool Scene::HandleSDLEvent() const
{
    if (!m_canContinueLoop)
        return false;

    const auto inputManager = m_engine->GetInputManager();
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_WINDOWEVENT:
        {
            if (event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                LOG_TO_CONSOLE(kSystem, "Window Closing.");
                return false;
            }
            break;
        }
        case SDL_KEYDOWN:
        {
            if (const SDL_Keycode keyDown = event.key.keysym.sym)
                inputManager->SetKey(keyDown, true);
            break;
        }
        case SDL_KEYUP:
        {
            if (const SDL_Keycode keyUp = event.key.keysym.sym)
                inputManager->SetKey(keyUp, false);
            break;
        }
        case SDL_MOUSEMOTION:
        {
            inputManager->SetMousePosition(static_cast<float>(event.button.x), static_cast<float>(event.button.y));
            m_sceneEntityManager.CheckWidgetsForButtonHighlight(inputManager->GetMousePosition().x, inputManager->GetMousePosition().y);
            break;
        }

        case SDL_MOUSEBUTTONDOWN:
        {
            //LMB
            if (event.button.button == 1)
            {
                inputManager->SetLeftMouseButtonState(true);
                m_sceneEntityManager.CheckWidgetsForButtonClick(inputManager->GetMousePosition().x, inputManager->GetMousePosition().y);
            }
            //RMB
            if (event.button.button == 2)
                inputManager->SetRightMouseButtonState(true);
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            //LMB
            if (event.button.button == 1)
                inputManager->SetLeftMouseButtonState(false);
            //RMB
            if (event.button.button == 2)
                inputManager->SetRightMouseButtonState(false);
            break;
        }
        default:
            break;
        }
    }
    return true;
}

void Scene::Render()
{
    m_sceneEntityManager.Render();
}

