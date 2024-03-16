#include "ButtonComponent.h"

#include "../../../../CoreSystems/MurphEngine.h"
#include "../../../../LoggingSystem/Logging.h"
#include "../PositionComponent/PositionComponent.h"

ButtonComponent::ButtonComponent(const char* imagePath)
    : m_pImagePath(imagePath)
    , m_pSystemRenderer(nullptr)
    , m_imageTintColor{255, 255, 255, 255}
    , m_highlightedTint{255, 255, 255, 255}
{
    const auto resource = MurphEngine::GetInstance();
    m_pSystemRenderer = resource->GetGraphicsManager()->GetRenderer();
    m_pTexture = resource->GetResourceManager()->GetImage(imagePath);

    m_componentName = "ButtonComponent";
}

ButtonComponent::~ButtonComponent() = default;

void ButtonComponent::Update([[maybe_unused]]double deltaTime)
{
    const auto position = static_cast<PositionComponent*>(m_pOwner->GetComponent("PositionComponent"));
    const auto rect = position->GetRect();

    if (position != nullptr)
        m_transform = { rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight()};
    else
        LOG_TO_CONSOLE(kError, "No position component found for button update");
}


void ButtonComponent::Render() const
{
    if (m_isHighlighted)
        SDL_SetTextureColorMod(m_pTexture, m_highlightedTint.r, m_highlightedTint.g, m_highlightedTint.b);
    else
        SDL_SetTextureColorMod(m_pTexture, m_imageTintColor.r, m_imageTintColor.g, m_imageTintColor.b);

    const SDL_FRect sdlRect{ m_transform.GetX(), m_transform.GetY(), m_transform.GetWidth(), m_transform.GetHeight() };
    SDL_RenderCopyF(m_pSystemRenderer, m_pTexture, nullptr, &sdlRect);
}

void ButtonComponent::Shutdown()
{
    Component::Shutdown();
}

/// <summary>
/// Set Text output to log for callback. This is to be used for testing purposes. 
/// </summary>
/// <param name="textcontents">Desired output.</param>
void ButtonComponent::SetCallbackAsDebugLogText(const std::string& textcontents)
{
    SetCallback([textcontents]()-> void
    {
        LOG_TO_CONSOLE(kGamePlay, textcontents);
    });
}

/// <summary>
/// Set Tint of button
/// </summary>
/// <param name="inRed">red value</param>
/// <param name="inGreen">green value</param>
/// <param name="inBlue">blue value</param>
/// <param name="inAlpha">alpha value</param>
void ButtonComponent::SetImageTintColor(uint8_t inRed, uint8_t inGreen, uint8_t inBlue, uint8_t inAlpha)
{
    m_imageTintColor = SDL_Color{ inRed, inGreen, inBlue,inAlpha };
}

/// <summary>
/// Set Tint of button highlight
/// </summary>
/// <param name="inRed">red value</param>
/// <param name="inGreen">green value</param>
/// <param name="inBlue">blue value</param>
/// <param name="inAlpha">alpha value</param>
void ButtonComponent::SetHighlightTintColor(uint8_t inRed, uint8_t inGreen, uint8_t inBlue, uint8_t inAlpha)
{
    m_highlightedTint = SDL_Color{ inRed, inGreen, inBlue,inAlpha };
}

/// <summary>
/// Call function callback when button is pressed
/// </summary>
void ButtonComponent::TriggerButton() const
{
    if (m_callback != nullptr)
        m_callback();
}


/// <summary>
/// Is Button Highlighted (mouse over)
/// </summary>
/// <param name="x">mouse x position</param>
/// <param name="y">mouse y position</param>
/// <returns></returns>
bool ButtonComponent::IsHighlighted(float x, float y)
{
    m_isHighlighted = HitTest(x, y);
    return m_isHighlighted;
}

/// <summary>
/// Check if mouse click is within button
/// </summary>
/// <param name="x">mouse X position</param>
/// <param name="y">mouse Y position</param>
/// <returns></returns>
bool ButtonComponent::HitTest(float x, float y)
{
    return m_transform.Contains({ x, y });
}

MurphRect ButtonComponent::OffsetButtonByJustification() const
{
    MurphRect offsetTransform = m_transform;

    switch (m_justification)
    {
    case ButtonJustification::kTopLeft:
        break;
    case ButtonJustification::kTopCenter:
    {
        offsetTransform.SetX(m_transform.GetX() + (m_transform.GetWidth() / 2)); // offset the width to center the text.
        break;
    }
    case ButtonJustification::kTopRight: //BUG: will go outside the edge. BAD SOLUTION.
    {
        offsetTransform.SetX(m_transform.GetX() + m_transform.GetWidth());
        break;
    }
    case ButtonJustification::kCenterLeft:
    {
        offsetTransform.SetY(m_transform.GetY() + (m_transform.GetHeight() / 2));
        break;
    }
    case ButtonJustification::kCenter:
    {
        auto center = m_transform.GetCenterPoint();
        offsetTransform.SetPosition(center);
        break;
    }
    case ButtonJustification::kCenterRight: //BUG: will go outside the edge. BAD SOLUTION.
    {

        offsetTransform.SetX(m_transform.GetX() + m_transform.GetWidth());
        offsetTransform.SetY(m_transform.GetY() + (m_transform.GetHeight() / 2));
        break;
    }
    case ButtonJustification::kBottomLeft:
    {
        offsetTransform.SetY(m_transform.GetY() + (m_transform.GetHeight()));
        break;
    }
    case ButtonJustification::kBottomCenter:
    {
        offsetTransform.SetX(m_transform.GetX() + (m_transform.GetWidth() / 2));
        offsetTransform.SetY(m_transform.GetY() + m_transform.GetHeight());
        break;
    }
    case ButtonJustification::kBottomRight: //BUG: will go outside the edge. BAD SOLUTION.
    {

        offsetTransform.SetX(m_transform.GetX() + m_transform.GetWidth());
        offsetTransform.SetY(m_transform.GetY() + m_transform.GetHeight());
        break;
    }
    case ButtonJustification::kError:
    default:
        break;
    }
    return offsetTransform;
}
