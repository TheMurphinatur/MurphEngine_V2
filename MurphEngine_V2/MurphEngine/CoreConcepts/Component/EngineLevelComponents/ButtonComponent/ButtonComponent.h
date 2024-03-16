#pragma once
#include <functional>
#include <utility>

#include "../../Component.h"
#include "../../../../Middleware/SDL2/include/SDL_render.h"
#include "../../../../Math/Rect.h"


class ButtonComponent : public Component
{
public:
    enum class ButtonJustification
    {
        kTopLeft,
        kTopCenter,
        kTopRight,
        kCenterLeft,
        kCenter,
        kCenterRight,
        kBottomLeft,
        kBottomCenter,
        kBottomRight,

        kError
    };

private:

protected:
    const char* m_pImagePath;
    std::string m_widgetName;
    SDL_Renderer* m_pSystemRenderer;
    SDL_Color m_imageTintColor;
    SDL_Color m_highlightedTint;
    ButtonJustification m_justification = ButtonJustification::kCenter;
    SDL_Texture* m_pTexture{ };
    MurphRect m_transform;
    MurphRect m_offsetTransform;

    bool m_isHighlighted = false;
    // Function that will execute on click.
    std::function<void()> m_callback;

public:
    ButtonComponent(const char* imagePath);
    virtual ~ButtonComponent() override;
    virtual void Update(double deltaTime) override;
    virtual void Render() const override;
    virtual void Shutdown() override;

    /// <summary>
    /// Set what happens when you click the button.
    /// </summary>
    /// <param name="callback">Function pointer to function on click.</param>
    void SetCallback(std::function<void()> callback) { m_callback = std::move(callback); }
    void SetCallbackAsDebugLogText(const std::string& textcontents);
    void SetJustification(ButtonJustification justification) { m_justification = justification; }
    virtual void SetImageTintColor(uint8_t inRed, uint8_t inGreen, uint8_t inBlue, uint8_t inAlpha);
    virtual void SetHighlightTintColor(uint8_t inRed, uint8_t inGreen, uint8_t inBlue, uint8_t inAlpha);
    virtual void TriggerButton() const;
    MurphRect GetButtonOffsetPosition() const { return m_offsetTransform; }

    bool IsHighlighted(float x, float y);
    void SetwidgetName(const std::string& name) { m_widgetName = name; }

    std::string GetName() { return m_widgetName; }

    /// <summary>
    /// Get state of button.
    /// </summary>
    /// <returns>True if button is pressed</returns>
    virtual bool GetButtonState() { return false; }

    /// <summary>
    /// Get the value of the button.
    /// </summary>
    /// <returns>button value</returns>
    virtual float GetButtonValue() { return 0.0f; }

protected:
    SDL_Color GetTextColor() const { return m_imageTintColor; }
    SDL_Color GetHighlightcolor() const { return m_highlightedTint; }
    virtual bool HitTest(float x, float y);
    virtual bool IsHighLighted() const { return m_isHighlighted; }

    MurphRect OffsetButtonByJustification() const;
};
