#pragma once

#include "../ButtonComponent.h"


class ToggleComponent final : public ButtonComponent
{
private:
    const char* m_pToggleImagePath;

    SDL_Color m_toggleTintColor;
    SDL_Texture* m_pToggleTexture{ };
    MurphRect m_toggleTransform;
    bool m_isSelected = false;

public:
    ToggleComponent(const char* backgroundImagePath, const char* toggleImagePath);
    virtual ~ToggleComponent() override;
    virtual void Update(double deltaTime) override;
    virtual void Render() const override;

    void SetToggleTintColor(uint8_t inRed, uint8_t inGreen, uint8_t inBlue, uint8_t inAlpha);

    virtual void TriggerButton() const override;

    bool IsSelected() const { return m_isSelected; }

    virtual bool GetButtonState() override { return IsSelected(); }
    virtual float GetButtonValue() override { return IsSelected(); }

private:
    void ToggleSelectedState() { m_isSelected = !m_isSelected; }

protected:
    virtual bool HitTest(float x, float y) override;
    virtual bool IsHighLighted() const override;
};