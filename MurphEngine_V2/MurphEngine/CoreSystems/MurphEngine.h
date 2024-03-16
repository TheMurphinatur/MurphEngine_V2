#pragma once

#include "Application/Application.h"
#include "AssetManagers/ResourceManager.h"
#include "GraphicsManager/GraphicsManager.h"
#include "InputManager/InputManager.h"
#include "LocalizationManager/LocalizationManager.h"
#include "TimeManager/TimeManager.h"
#include "SceneManager/SceneManager.h"

/// <summary>
/// Engine is the "Manager of Managers"
/// </summary>
class MurphEngine final
{
    inline static MurphEngine* s_pInstance = nullptr;

    GraphicsManager m_graphicsManager;
    InputManager m_pInputManager;
    TimeManager m_pTimeManager;
    ResourceManager m_resourceManager;
    SceneManager m_sceneManager;
    LocalizationManager m_localizationManager;
    Application* m_pApplication = nullptr;

public:

    // Static functions.
    static MurphEngine* GetInstance();

    // Shuts Down instance and cleans up memory.
    static void ShutDown();

    // Manager Getters.

    /// <summary>
    /// Get Graphics Manager
    /// </summary>
    /// <returns> Pointer to Engine Graphics Manager</returns>
    GraphicsManager* GetGraphicsManager()  { return &m_graphicsManager; }

    /// <summary>
    /// Get Input Manager
    /// </summary>
    /// <returns> Pointer to Engine Input Manager</returns>
    InputManager* GetInputManager() { return &m_pInputManager; }

    /// <summary>
    /// Get Time Manager
    /// </summary>
    /// <returns> Pointer to Engine Time Manager</returns>
    TimeManager* GetTimeManager() { return &m_pTimeManager; }

    /// <summary>
    /// Get Resource Manager
    /// </summary>
    /// <returns> Pointer to Engine Resource Manager</returns>
    ResourceManager* GetResourceManager()  { return &m_resourceManager; }

    /// <summary>
    /// Get Scene Manager
    /// </summary>
    /// <returns> Pointer to Engine Scene Manager</returns>
    SceneManager* GetSceneManager() { return &m_sceneManager; }

    /// <summary>
    /// Get Current Game Application. it should be a subclass of application so, we cast to game application as necessary.
    /// </summary>
    /// <returns>Current Application running the engine.</returns>
    Application* GetApplication() const { return m_pApplication; }

    /// <summary>
    /// Get Localization Manager. This contains all localized strings
    /// </summary>
    /// <returns> Manager of localized strings.</returns>
    LocalizationManager* GetLocalizationManager() { return &m_localizationManager; }

    /// <summary>
    /// Set the main game application. this will let us access certain managers within the application from the engine instance.
    /// </summary>
    /// <param name="pApplication">Main game application</param>
    void SetGameApplication(Application* pApplication) { m_pApplication = pApplication; }

    bool Update([[maybe_unused]] double deltaTime = 0.0);

    ~MurphEngine();
protected:
    bool ProcessSDLEvents() const;
    void Render() const;
private:
    MurphEngine();
};