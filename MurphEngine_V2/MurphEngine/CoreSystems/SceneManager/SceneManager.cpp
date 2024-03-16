#include "SceneManager.h"

#include <ranges>

#include "../../LoggingSystem/Logging.h"
#include "../SceneManager/Scene/Scene.h"
#include "Bleach_New/BleachNew.h"

SceneManager::SceneManager()
    : m_pCurrentScene(nullptr)
{
    m_pSceneList.reserve(20);
}

SceneManager::~SceneManager()
{
    for (const auto& val : m_pSceneList | std::views::values)
        BLEACH_DELETE(val);
    m_pSceneList.clear();
}


/**
 * \brief If no scene queued for switch, update current scene
 * \param deltaTime delta time
 * \return 
 */
bool SceneManager::Update(double deltaTime)
{
    if (m_nextSceneName != "None")
    {
        ChangeScene(m_nextSceneName);
        m_nextSceneName = "None";

        if (!m_pSceneList.at(m_currentSceneName)->HasBeenInitialized())
            m_pSceneList.at(m_currentSceneName)->Initialize();
    }

    if (m_pCurrentScene == nullptr)
    {
        LOG_TO_CONSOLE(kError, "No scene loaded.");
        return false; // no scene. no play.
    }

    return m_pCurrentScene->Update(deltaTime);
}

/**
 * \brief Render current scene
 */
void SceneManager::Render() const
{
    if (m_pCurrentScene != nullptr)
        m_pCurrentScene->Render();
}

/**
 * \brief Calls on current scene to handle SDL event.
 * \return true or false if scene handled event.
 */
bool SceneManager::HandleSDLEvent() const
{
    if (m_pCurrentScene != nullptr)
    {
        return m_pCurrentScene->HandleSDLEvent();
    }
    return true;
}

/**
 * \brief Queue new scene for scene change.
 * \param requestedScene Scene to Open
 * \return true if requested scene queued up.
 */
bool SceneManager::ChangeScene(const std::string& requestedScene)
{
    if (!m_pSceneList.contains(requestedScene))
        return false;

    // set previous scene name and update current scene name
    m_prevSceneName = m_currentSceneName;
    m_currentSceneName = requestedScene;

    // Set new Scene.
    m_pCurrentScene = m_pSceneList.at(requestedScene);
    m_pCurrentScene->SetPreviousSceneName(m_prevSceneName);

    return true;
}

/**
 * \brief Get Previous scene (if applicable) and queue for scene change.
 */
void SceneManager::ActivatePreviousScene()
{
    if (m_prevSceneName != "None")
    {
        const auto previousSceneName = m_pCurrentScene->GetPreviousSceneName();
        m_pCurrentScene->DeActivateScene();
        m_pCurrentScene = m_pSceneList.at(previousSceneName);
        m_currentSceneName = previousSceneName;
        return;
    }

    LOG_TO_CONSOLE(kError, "Tried to load previous scene on first loaded scene.");
}

/**
 * \brief Add New Scene to Scene Map
 * \param sceneName Name of scene for search
 * \param newScene Scene Pointer.
 * \return Given scene.
 */
bool SceneManager::AddNewScene(const std::string& sceneName, Scene* newScene)
{
    const auto didEmplace = m_pSceneList.emplace(sceneName, newScene);

    return didEmplace.second;
}


/**
 * \brief Get Scene by name
 * \param sceneName Requested Scene Name
 * \return nullptr if no scene found.
 */
Scene* SceneManager::GetSceneByName(const std::string& sceneName) const
{
    if (!m_pSceneList.contains(sceneName))
        return nullptr;

    return m_pSceneList.at(sceneName);
}

/**
 * \brief Queue scene for load.
 * \param sceneName Scene name to load
 */
void SceneManager::LoadScene(const std::string& sceneName)
{
    if (m_pSceneList.contains(sceneName))
        m_nextSceneName = sceneName;
    else
        LOG_TO_CONSOLE(kError, std::string("No Scene Found with name: " + sceneName));
}

