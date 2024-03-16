#pragma once

#include <SDL_render.h>

#include "../../../../../Math/Rect.h"
#include "../../ButtonComponent/ButtonComponent.h"

class CheckBoxComponent final : public ButtonComponent
{

private:
    const char* m_pCheckImagePath = nullptr;
    bool m_isSelected = false;

    SDL_Color m_checkTintColor;
    SDL_Texture* m_pCheckTexture{ };
    MurphRect m_boxTransform;
    MurphRect m_checkMarkTransform;
public:
    CheckBoxComponent(const char* boxImagePath, const char* checkImagePath);
    virtual ~CheckBoxComponent() override;
    virtual void Initialize() override;
    virtual void Shutdown() override;
    virtual void Update(double deltaTime) override;
    virtual void Render() const override;

    void SetBoxTintColor(uint8_t inRed, uint8_t inGreen, uint8_t inBlue, uint8_t inAlpha);
    void SetBoxHighlightTintColor(uint8_t inRed, uint8_t inGreen, uint8_t inBlue, uint8_t inAlpha);
    void SetMarkTintColor(uint8_t inRed, uint8_t inGreen, uint8_t inBlue, uint8_t inAlpha);
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


