#pragma once
#include <string>

#include "../../MurphEngine.h"
#include "../../EntityManager/EntityManager.h"


class Scene
{
protected:
    const char* m_sceneXMLPath = nullptr;
    bool m_canContinueLoop = true;
    bool m_isActive = false;
    bool m_hasBeenInitialized = false;
    EntityManager m_sceneEntityManager;
    std::string m_previouSceneName = "None";

    MurphEngine* m_engine;
    SDL_Texture* m_backgroundTexture;

public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void Initialize();
    virtual void ChangeScene(const std::string& sceneName);

    virtual bool Update([[maybe_unused]] double deltaTime);
    bool HandleSDLEvent() const;
    virtual void Render();

    EntityManager* GetEntityManager() { return &m_sceneEntityManager; }

    virtual void CleanupScene() { };

    void ActivateScene() { m_isActive = true; }
    void DeActivateScene() { m_isActive = false; }

    virtual bool CanContinue() const { return m_canContinueLoop; }
    void QuitScene() { m_canContinueLoop = false; }

    bool HasBeenInitialized() const { return m_hasBeenInitialized; }

    void SetPreviousSceneName(const std::string& name) { m_previouSceneName = name; }
    std::string GetPreviousSceneName() { return m_previouSceneName; }

protected:
};
