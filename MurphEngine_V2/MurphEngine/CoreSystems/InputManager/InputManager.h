#pragma once

#include "../../Middleware/SDL2/include/SDL.h"
//#include <SDL.h>
#include <unordered_map>

#include "../Math/Vector.h"

class InputManager
{
public:
    // public enum for the keys we want to use
    enum MurphKey
    {
        MurphKey_a = SDLK_a,
        MurphKey_b = SDLK_b,
        MurphKey_c = SDLK_c,
        MurphKey_d = SDLK_d,
        MurphKey_e = SDLK_e,
        MurphKey_f = SDLK_f,
        MurphKey_g = SDLK_g,
        MurphKey_h = SDLK_h,
        MurphKey_i = SDLK_i,
        MurphKey_j = SDLK_j,
        MurphKey_k = SDLK_k,
        MurphKey_l = SDLK_l,
        MurphKey_m = SDLK_m,
        MurphKey_n = SDLK_n,
        MurphKey_o = SDLK_o,
        MurphKey_p = SDLK_p,
        MurphKey_q = SDLK_q,
        MurphKey_r = SDLK_r,
        MurphKey_s = SDLK_s,
        MurphKey_t = SDLK_t,
        MurphKey_u = SDLK_u,
        MurphKey_v = SDLK_v,
        MurphKey_w = SDLK_w,
        MurphKey_x = SDLK_x,
        MurphKey_y = SDLK_y,
        MurphKey_z = SDLK_z,
        MurphKey_0 = SDLK_0,
        MurphKey_1 = SDLK_1,
        MurphKey_2 = SDLK_2,
        MurphKey_3 = SDLK_3,
        MurphKey_4 = SDLK_4,
        MurphKey_5 = SDLK_5,
        MurphKey_6 = SDLK_6,
        MurphKey_7 = SDLK_7,
        MurphKey_8 = SDLK_8,
        MurphKey_9 = SDLK_9,
        MurphKey_ESC = SDLK_ESCAPE,
        MurphKey_SPACE = SDLK_SPACE,
        MurphKey_LCTRL = SDLK_LCTRL,
        MurphKey_LSHIFT = SDLK_LSHIFT,
        MurphKey_LALT = SDLK_LALT,
        MurphKey_PGUP = SDLK_PAGEUP,
        MurphKey_PGDOWN = SDLK_PAGEDOWN,
        MurphKey_ArrowUp = SDLK_UP,
        MurphKey_ArrowDown = SDLK_DOWN,
        MurphKey_ArrowLeft = SDLK_LEFT,
        MurphKey_ArrowRight = SDLK_RIGHT
        //kDefault
    };
protected:
    struct KeyState
    {
    private:

        bool m_isPressed = false;
        double m_heldTime = 0.0;

    public:
        bool IsKeyPressed() const { return m_isPressed; }
        void SetKeyState(bool state)
        {
            m_isPressed = state;
            if (!m_isPressed) // if key is released, reset the time
                ResetTime();
        }

        void AddTime(double deltaTime) { m_heldTime += deltaTime; }
        double GetTimeHeld() const { return m_heldTime; }
        double GetTimeHeldInSeconds() const { return m_heldTime / 1000.0; }

    private:
        void ResetTime() { m_heldTime = 0.0; }
    };

private:
    std::unordered_map<MurphKey, KeyState> m_keys;
    Vector2<float> m_mousePosition = { 0.f ,0.f};
    Vector2<bool> m_mouseButtonState = {false, false};

public:
    InputManager();
    ~InputManager();
    void Update(double deltaTime);


    void SetKey(SDL_Keycode key, bool isPressed);
    void SetMousePosition(float x, float y) { m_mousePosition = Vector2( x, y); }
    void SetMouseButtonState(bool leftPressed, bool rightPressed) { m_mouseButtonState = Vector2(leftPressed, rightPressed); }
    void SetLeftMouseButtonState(bool isPressed) { m_mouseButtonState.x = isPressed; }
    void SetRightMouseButtonState(bool isPressed) { m_mouseButtonState.y = isPressed; }

    Vector2<float> GetMousePosition() const { return m_mousePosition; }
    bool IsLeftMouseButtonPressed() const { return m_mouseButtonState.x; }
    bool IsRightMouseButtonPressed() const { return m_mouseButtonState.y; }
    bool IsKeyPressed(MurphKey key);
    bool IsKeyHeld(MurphKey key);

protected:
    void UpdateKeyState(double deltaTime);
    bool AddKeyToList(MurphKey key);
    void RemoveKeyFromList(MurphKey key);
};








