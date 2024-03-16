#include "CheckBoxComponent.h"


#include "../../../../../CoreSystems/MurphEngine.h"
#include "../../PositionComponent/PositionComponent.h"


CheckBoxComponent::CheckBoxComponent(const char* boxImagePath, const char* checkImagePath)
    : ButtonComponent(boxImagePath)
    , m_pCheckImagePath(checkImagePath)
    , m_checkTintColor()
{
    const auto resource = MurphEngine::GetInstance();
    m_pSystemRenderer = resource->GetGraphicsManager()->GetRenderer();
    m_pCheckImagePath = checkImagePath;
    m_pCheckTexture = resource->GetResourceManager()->GetImage(checkImagePath);

    m_componentName = "CheckBoxComponent";

    SetCallback([this]()-> void
        {
            ToggleSelectedState();
        });
}

CheckBoxComponent::~CheckBoxComponent()
{
    SDL_DestroyTexture(m_pCheckTexture);
}

void CheckBoxComponent::Initialize()
{
    Component::Initialize();
}

void CheckBoxComponent::Shutdown()
{
	ButtonComponent::Shutdown();
}

void CheckBoxComponent::Update([[maybe_unused]] double deltaTime)
{
    const auto position = static_cast<PositionComponent*>(m_pOwner->GetComponent("PositionComponent"));
    const auto rect = position->GetRect();

    if (position != nullptr)
        m_transform = { rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight()};
    else
        LOG_TO_CONSOLE(kError, "No position component found for button update");
}

void CheckBoxComponent::Render() const
{
    const SDL_FRect sdlRect{ m_transform.GetX(), m_transform.GetY(), m_transform.GetWidth(), m_transform.GetHeight() };
    if (!m_isSelected)
		SDL_SetTextureColorMod(m_pTexture, m_imageTintColor.r, m_imageTintColor.g, m_imageTintColor.b);
    else
        SDL_SetTextureColorMod(m_pTexture, m_highlightedTint.r, m_highlightedTint.g, m_highlightedTint.b);
    SDL_RenderCopyF(m_pSystemRenderer, m_pTexture, nullptr, &sdlRect);

    if (m_isSelected)
    {
        const SDL_FRect checkRect{ m_transform.GetX() + (m_transform.GetWidth() * 0.12f), m_transform.GetY() + (m_transform.GetHeight() * 0.12f), m_transform.GetWidth() * 0.75f, m_transform.GetHeight() * 0.75f};
        // color and render the check mark on top of the box.
        SDL_SetTextureColorMod(m_pCheckTexture, m_checkTintColor.r, m_checkTintColor.g, m_checkTintColor.b);
        SDL_RenderCopyF(m_pSystemRenderer, m_pCheckTexture, nullptr, &checkRect);
    }
}

void CheckBoxComponent::SetBoxTintColor(uint8_t inRed, uint8_t inGreen, uint8_t inBlue, uint8_t inAlpha)
{
    ButtonComponent::SetImageTintColor(inRed, inGreen, inBlue, inAlpha);
}

void CheckBoxComponent::SetBoxHighlightTintColor(uint8_t inRed, uint8_t inGreen, uint8_t inBlue, uint8_t inAlpha)
{
    ButtonComponent::SetHighlightTintColor(inRed, inGreen, inBlue, inAlpha);
}

void CheckBoxComponent::SetMarkTintColor(uint8_t inRed, uint8_t inGreen, uint8_t inBlue, uint8_t inAlpha)
{
    m_checkTintColor = {inRed, inGreen, inBlue, inAlpha};
}

void CheckBoxComponent::TriggerButton() const
{
    ButtonComponent::TriggerButton();
}

bool CheckBoxComponent::HitTest(float x, float y)
{
    return ButtonComponent::HitTest(x, y);
}

bool CheckBoxComponent::IsHighLighted() const
{
    return ButtonComponent::IsHighLighted();
}


