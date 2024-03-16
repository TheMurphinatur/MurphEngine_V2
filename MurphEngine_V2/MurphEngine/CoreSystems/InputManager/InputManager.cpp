#include "InputManager.h"
#include "../LoggingSystem/Logging.h"

#include <ranges>

/**
 * \brief Initialize Input Manager and reserve space for 10 keys in map
 */
InputManager::InputManager()
{
    m_keys.reserve(10);
}

/**
 * \brief Clean up Input Manager and clear all key values from map
 */
InputManager::~InputManager()
{
    m_keys.clear();
}

/**
 * \brief update Input Manager
 * \param deltaTime delta time
 */
void InputManager::Update(double deltaTime)
{
    UpdateKeyState(deltaTime);
}

/**
 * \brief Update The state of the keys, currently only used to determine how long a key has been held.
 * \param deltaTime delta time
 */
void InputManager::UpdateKeyState(double deltaTime)
{
    for (auto& data : m_keys | std::views::values)
    {
        if (data.IsKeyPressed())
            data.AddTime(deltaTime);//Log here if necessary.
    }
}

/**
 * \brief Set Key State
 * \param key key pressed
 * \param isPressed state of key press
 */
void InputManager::SetKey(SDL_Keycode key, bool isPressed)
{
    MurphKey murphKey = static_cast<MurphKey>(key);

    if (const auto search = m_keys.find(murphKey); search != m_keys.end())
    {
        // if key is already matching the value, return
        if (search->second.IsKeyPressed() == isPressed)
            return;

        // else set the key state
        search->second.SetKeyState(isPressed);
    }
    else
    {
      
        AddKeyToList(murphKey);
        m_keys[murphKey].SetKeyState(isPressed);
    }
}

/**
 * \brief Find out if a key is currently pressed
 * \param key key to check
 * \return true if currently pressed
 */
bool InputManager::IsKeyPressed(MurphKey key)
{
    if (const auto search = m_keys.find(key); search != m_keys.end())
    {
        if (search->second.IsKeyPressed())
            return true;
    }
    return false;
}

/**
 * \brief Get boolean on key hold status.
 * \param key key to check
 * \return if key is held down
 */
bool InputManager::IsKeyHeld(MurphKey key)
{
    if (const auto search = m_keys.find(key); search != m_keys.end())
    {
        if (search->second.IsKeyPressed() && search->second.GetTimeHeld() > 2.0)
            return true;
    }
    return false;
}

/**
 * \brief Remove Key from list of keys pressed.
 * \param key key to remove
 */
void InputManager::RemoveKeyFromList(MurphKey key)
{
    if (m_keys.contains(key))
        m_keys.erase(key);
}

/**
 * \brief Add key to list and get status of addition.
 * \param key key to add
 * \return true if added successfully false if already exists
 */
bool InputManager::AddKeyToList(MurphKey key)
{
    if (!m_keys.contains(key))
    {
        m_keys.insert({ key, KeyState()});
        return true;
    }
    return false;
}