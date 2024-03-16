#pragma once
#include "../ButtonComponent.h"


class DynamicBarComponent : public ButtonComponent
{
private:
    const char* m_barImagePath;

    SDL_Color m_knobTintColor;
    SDL_Texture* m_pBarTexture{ };

    MurphRect m_BarTransform; // TODO: this.

    float m_selectedBarDistance;

    float m_currentBarValue;
    float m_minBarValue;
    float m_maxBarValue;

public:
    DynamicBarComponent(const char* trayImagePath, const char* barImagePath);

    virtual ~DynamicBarComponent() override;
    virtual void Update(double deltaTime) override;
    virtual void Render() const override;

    void SetKnobTintColor(uint8_t inRed, uint8_t inGreen, uint8_t inBlue, uint8_t inAlpha);
    virtual void TriggerButton() const override;

    float GetKnobValue() const { return m_currentBarValue; }
    void SetMinimumBarValue(float minVal) { m_minBarValue = minVal; }
    void SetMaximumBarValue(float maxVal) { m_maxBarValue = maxVal; }
    float GetCurrentBarValue() const;
    void SetNewBarValue(float newVal);

    void SetBarSize(float width, float height);

    virtual float GetButtonValue() override { return m_currentBarValue; }

private:
    void SetBarPosition(float newX, float newY);
    void UpdateKnobPosition(float newXposition);
};
