#pragma once
#include "../ButtonComponent.h"


class SliderComponent final : public ButtonComponent
{
private:
    const char* m_pKnobImagePath;

    SDL_Color m_knobTintColor;
    SDL_Texture* m_pKnobTexture{ };

    MurphRect m_KnobTransform; // TODO: this.

    float m_selectedKnobDistance;

    float m_currentKnobValue;
    float m_minKnobValue;
    float m_maxKnobValue;

    float m_sliderMaxPosition;
    float m_sliderMinPosition;
    float m_currentSliderPosition;

public:
    SliderComponent(const char* trayImagePath, const char* knobImagePath);

    virtual ~SliderComponent() override;
    virtual void Update(double deltaTime) override;
    virtual void Render() const override;

    void SetKnobTintColor(uint8_t inRed, uint8_t inGreen, uint8_t inBlue, uint8_t inAlpha);
    virtual void TriggerButton() const override;

    float GetKnobValue() const { return m_currentKnobValue; }
    void SetMinimumSliderValue(float minVal) { m_minKnobValue = minVal; }
    void SetMaximumSliderValue(float maxVal) { m_maxKnobValue = maxVal; }
    float GetCurrentKnobValue() const;
    void SetNewKnobValue(float newVal);

    void SetKnobSize(float width, float height);
    void SetKnobPosition(float newX);

    virtual float GetButtonValue() override { return m_currentKnobValue; }


private:
    void UpdateKnobPosition(float newXposition);

protected:
    virtual bool HitTest(float x, float y) override;
    virtual bool IsHighLighted() const override;
};
