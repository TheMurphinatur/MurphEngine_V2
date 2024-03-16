#include "SliderComponent.h"
#include "../../../../../CoreSystems/MurphEngine.h"
#include "../../PositionComponent/PositionComponent.h"

SliderComponent::SliderComponent(const char* trayImagePath, const char* knobImagePath)
    : ButtonComponent(trayImagePath)
    , m_pKnobImagePath(knobImagePath)
{
    auto resource = MurphEngine::GetInstance();
    m_pSystemRenderer = resource->GetGraphicsManager()->GetRenderer();
    m_pKnobTexture = resource->GetResourceManager()->GetImage(knobImagePath);

    SetComponentName("SliderComponent");
}

SliderComponent::~SliderComponent()
{
    SDL_DestroyTexture(m_pKnobTexture);
}


void SliderComponent::Update([[maybe_unused]] double deltaTime)
{
    auto position = static_cast<PositionComponent*>(m_pOwner->GetComponent("PositionComponent"));
    auto rect = position->GetRect();
    if (position != nullptr)
    {
        m_transform = { rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight() };
    }
    else
    {
        LOG_TO_CONSOLE(kError, "No position component found for button update");
    }

    const float verticalOffset = rect.GetY() - m_KnobTransform.GetHalfHeight() + m_transform.GetHalfHeight();
    m_KnobTransform.SetY(verticalOffset);

    m_sliderMinPosition = rect.GetX() + m_KnobTransform.GetHalfWidth();
    m_sliderMaxPosition = (rect.GetX() + rect.GetWidth()) - m_KnobTransform.GetHalfWidth();

    if (m_currentSliderPosition < m_sliderMinPosition)
    {
        m_currentSliderPosition = m_sliderMinPosition;
    }

    m_selectedKnobDistance = (m_currentSliderPosition - m_sliderMinPosition) / (m_sliderMaxPosition - m_sliderMinPosition);

    if (m_selectedKnobDistance < 0.f || m_selectedKnobDistance > 1.0f)
    {
        m_selectedKnobDistance = 0.f;
    }

    m_currentKnobValue = MurphMath::Interpolate(m_minKnobValue, m_maxKnobValue, m_selectedKnobDistance);

    float sliderOffsetByVal = MurphMath::Interpolate(m_sliderMinPosition, m_sliderMaxPosition, m_selectedKnobDistance);

    m_KnobTransform.SetX(sliderOffsetByVal - m_KnobTransform.GetHalfWidth());
}

void SliderComponent::Render() const
{
    // render the tray
    const SDL_FRect sdlRect{ m_transform.GetX(), m_transform.GetY(), m_transform.GetWidth(), m_transform.GetHeight() };
    SDL_SetTextureColorMod(m_pTexture, m_imageTintColor.r, m_imageTintColor.g, m_imageTintColor.b);
    SDL_RenderCopyF(m_pSystemRenderer, m_pTexture, nullptr, &sdlRect);

    // render the Knob

    SDL_FRect checkRect{ m_KnobTransform.GetX() , m_KnobTransform.GetY(), m_KnobTransform.GetWidth(), m_KnobTransform.GetHeight() };

    SDL_SetTextureColorMod(m_pKnobTexture, m_knobTintColor.r, m_knobTintColor.g, m_knobTintColor.b);
    SDL_RenderCopyF(m_pSystemRenderer, m_pKnobTexture, nullptr, &checkRect);
}

void SliderComponent::SetKnobTintColor(uint8_t inRed, uint8_t inGreen, uint8_t inBlue, uint8_t inAlpha)
{
    m_knobTintColor = { inRed, inGreen, inBlue, inAlpha };
}

void SliderComponent::TriggerButton() const
{
    ButtonComponent::TriggerButton();
}

float SliderComponent::GetCurrentKnobValue() const
{
    return m_currentKnobValue;
}

void SliderComponent::SetNewKnobValue(float newVal)
{
    if (newVal < m_minKnobValue)
    {
        m_currentKnobValue = m_minKnobValue;
        LOG_TO_CONSOLE(kError, "New Knob Value Set below minimum value. Adjusting to min value.");
        return;
    }
    if (newVal > m_maxKnobValue)
    {
        m_currentKnobValue = m_maxKnobValue;
        LOG_TO_CONSOLE(kError, "New Knob Value Set above maximum value. Adjusting to max value.");
        return;
    }

    m_currentKnobValue = newVal;
}

void SliderComponent::SetKnobSize(float width, float height)
{
    m_KnobTransform.SetWidth(width);
    m_KnobTransform.SetHeight(height);
}

void SliderComponent::SetKnobPosition(float newX)
{
    if (newX >= m_sliderMinPosition && newX <= m_sliderMaxPosition)
    {
        m_currentSliderPosition = newX;
    }
    //m_KnobTransform.SetX(newX);

}

void SliderComponent::UpdateKnobPosition(float newXposition)
{
    m_KnobTransform.SetX(newXposition);
}

bool SliderComponent::HitTest(float x, float y)
{
    if (m_KnobTransform.Contains({ x,y }) || m_transform.Contains({x,y}))
    {
        return true;
    }

    return ButtonComponent::HitTest(x, y);
}

bool SliderComponent::IsHighLighted() const
{
    return ButtonComponent::IsHighLighted();
}
