#include "ToggleComponent.h"
#include "../../../../../CoreSystems/MurphEngine.h"
#include "../../PositionComponent/PositionComponent.h"

ToggleComponent::ToggleComponent(const char* backgroundImagePath, const char* toggleImagePath)
    : ButtonComponent(backgroundImagePath)
    , m_pToggleImagePath(toggleImagePath)
{
    const auto resource = MurphEngine::GetInstance();
    m_pSystemRenderer = resource->GetGraphicsManager()->GetRenderer();
    m_pToggleTexture = resource->GetResourceManager()->GetImage(toggleImagePath);

    m_componentName = "ToggleComponent";

    SetCallback([this]()-> void
        {
            ToggleSelectedState();
        });
}

ToggleComponent::~ToggleComponent()
{
    SDL_DestroyTexture(m_pToggleTexture);
}

void ToggleComponent::Update([[maybe_unused]]double deltaTime)
{
    const auto position = static_cast<PositionComponent*>(m_pOwner->GetComponent("PositionComponent"));
    const auto rect = position->GetRect();

    m_toggleTransform.SetWidth(rect.GetHalfWidth() * .8f);
    m_toggleTransform.SetHeight(rect.GetHeight() * .8f);

    if (position != nullptr)
    {
        m_transform = { rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight() };
    }
    else
    {
        LOG_TO_CONSOLE(kError, "No position component found for button update");
    }

    m_toggleTransform.SetY(m_transform.GetY() + m_transform.GetHeight() * .1f);

    if (m_isSelected)
    {
        m_toggleTransform.SetX(m_transform.GetX() + m_toggleTransform.GetWidth() + m_toggleTransform.GetHalfWidth() * .8f);
    }
    else
    {
        m_toggleTransform.SetX(m_transform.GetX() + m_transform.GetWidth() * .05f);
    }

}

void ToggleComponent::Render() const
{
    const SDL_FRect sdlRect{ m_transform.GetX(), m_transform.GetY(), m_transform.GetWidth(), m_transform.GetHeight() };
    const SDL_FRect checkRect{ m_toggleTransform.GetX(), m_toggleTransform.GetY(), m_toggleTransform.GetWidth(), m_toggleTransform.GetHeight() };
    // render the box
    if (!m_isSelected)
    {
        SDL_SetTextureColorMod(m_pTexture, m_imageTintColor.r, m_imageTintColor.g, m_imageTintColor.b);
        SDL_SetTextureColorMod(m_pToggleTexture, m_imageTintColor.r, m_imageTintColor.g, m_imageTintColor.b);
    }
    else
    {
        SDL_SetTextureColorMod(m_pTexture, m_highlightedTint.r, m_highlightedTint.g, m_highlightedTint.b);
        SDL_SetTextureColorMod(m_pToggleTexture, m_highlightedTint.r, m_highlightedTint.g, m_highlightedTint.b);
        // render the check mark
    }
    SDL_RenderCopyF(m_pSystemRenderer, m_pTexture, nullptr, &sdlRect);
    SDL_RenderCopyF(m_pSystemRenderer, m_pToggleTexture, nullptr, &checkRect);

}

void ToggleComponent::SetToggleTintColor(uint8_t inRed, uint8_t inGreen, uint8_t inBlue, uint8_t inAlpha)
{
    m_toggleTintColor = { inRed, inGreen, inBlue, inAlpha };
}

void ToggleComponent::TriggerButton() const
{
    ButtonComponent::TriggerButton();
}

bool ToggleComponent::HitTest(float x, float y)
{
    return ButtonComponent::HitTest(x, y);
}

bool ToggleComponent::IsHighLighted() const
{
    return ButtonComponent::IsHighLighted();
}
