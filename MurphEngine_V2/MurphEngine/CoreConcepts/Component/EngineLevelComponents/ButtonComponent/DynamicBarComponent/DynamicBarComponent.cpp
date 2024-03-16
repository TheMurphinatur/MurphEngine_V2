#include "DynamicBarComponent.h"

#include "../../../../../../DemoProject/GameApplication/GameComponents/Health/HealthComponent.h"
#include "../../../../../CoreSystems/MurphEngine.h"
#include "../../../../../CoreSystems/SceneManager/Scene/Scene.h"
#include "../../PositionComponent/PositionComponent.h"

DynamicBarComponent::DynamicBarComponent(const char* trayImagePath, const char* barImagePath)
    : ButtonComponent(trayImagePath)
    , m_barImagePath(barImagePath)
{
    auto resource = MurphEngine::GetInstance();
    m_pSystemRenderer = resource->GetGraphicsManager()->GetRenderer();
    m_pBarTexture = resource->GetResourceManager()->GetImage(barImagePath);

    SetComponentName("DynamicBarComponent");
}

DynamicBarComponent::~DynamicBarComponent()
{
    SDL_DestroyTexture(m_pBarTexture);
}


void DynamicBarComponent::Update([[maybe_unused]] double deltaTime)
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
    m_BarTransform.SetX(rect.GetX());
    m_BarTransform.SetY(rect.GetY());

    constexpr auto m_sliderMinWidth = 0.f;
    const auto m_sliderMaxWidth = rect.GetWidth();

    m_selectedBarDistance = (m_currentBarValue - m_minBarValue) / (m_maxBarValue - m_minBarValue);
    if (m_selectedBarDistance < 0.f || m_selectedBarDistance > 1.0f)
        m_selectedBarDistance = 0.f;

    const float barWidth = MurphMath::Interpolate(m_sliderMinWidth, m_sliderMaxWidth, m_selectedBarDistance);

    m_BarTransform.SetWidth(barWidth);
    m_BarTransform.SetHeight(rect.GetHeight());
}

void DynamicBarComponent::Render() const
{
    // render the tray
    const SDL_FRect sdlRect{ m_transform.GetX(), m_transform.GetY(), m_transform.GetWidth(), m_transform.GetHeight() };
    SDL_SetTextureColorMod(m_pTexture, m_imageTintColor.r, m_imageTintColor.g, m_imageTintColor.b);
    SDL_RenderCopyF(m_pSystemRenderer, m_pTexture, nullptr, &sdlRect);

    // render the Knob

    SDL_FRect checkRect{ m_BarTransform.GetX() , m_BarTransform.GetY(), m_BarTransform.GetWidth(), m_BarTransform.GetHeight() };

    SDL_SetTextureColorMod(m_pBarTexture, m_knobTintColor.r, m_knobTintColor.g, m_knobTintColor.b);
    SDL_RenderCopyF(m_pSystemRenderer, m_pBarTexture, nullptr, &checkRect);
}

void DynamicBarComponent::SetKnobTintColor(uint8_t inRed, uint8_t inGreen, uint8_t inBlue, uint8_t inAlpha)
{
    m_knobTintColor = { inRed, inGreen, inBlue, inAlpha };
}

void DynamicBarComponent::TriggerButton() const
{
    ButtonComponent::TriggerButton();
}

float DynamicBarComponent::GetCurrentBarValue() const
{
    return m_currentBarValue;
}

void DynamicBarComponent::SetNewBarValue(float newVal)
{
    if (newVal < m_minBarValue)
    {
        m_currentBarValue = m_minBarValue;
        LOG_TO_CONSOLE(kError, "New Knob Value Set below minimum value. Adjusting to min value.");
        return;
    }
    if (newVal > m_maxBarValue)
    {
        m_currentBarValue = m_maxBarValue;
        LOG_TO_CONSOLE(kError, "New Knob Value Set above maximum value. Adjusting to max value.");
        return;
    }

    m_currentBarValue = newVal;
}

void DynamicBarComponent::SetBarSize(float width, float height)
{
    m_BarTransform.SetWidth(width);
    m_BarTransform.SetHeight(height);
}

void DynamicBarComponent::SetBarPosition(float newX, float newY)
{
    m_BarTransform.SetX(newX);
    m_BarTransform.SetY(newY);
}

void DynamicBarComponent::UpdateKnobPosition(float newXposition)
{
    m_BarTransform.SetX(newXposition);
}
