#pragma once
#include <string>
#include <unordered_map>

class Scene;

class SceneManager final
{
protected:
    bool m_isSceneActive = false;

    std::unordered_map<std::string, Scene*> m_pSceneList;

    // Scene management strings. 
    std::string m_prevSceneName = "None";
    std::string m_currentSceneName = "None";
    std::string m_nextSceneName = "None";
    Scene* m_pCurrentScene;

public:
    SceneManager();
    ~SceneManager();

    bool Update([[maybe_unused]] double deltaTime);
    void Render() const;
    bool HandleSDLEvent() const;
    bool ChangeScene(const std::string& requestedSceneName);

    // Scene management functions.

    void ActivatePreviousScene();
    bool AddNewScene(const std::string& sceneName, Scene* newScene);
    /**
     * \brief Get Current Scene pointer
     * \return current scene
     */
    Scene* GetCurrentScene() const { return m_pCurrentScene; }
    Scene* GetSceneByName(const std::string& sceneName) const;
    void LoadScene(const std::string& sceneName);


};
