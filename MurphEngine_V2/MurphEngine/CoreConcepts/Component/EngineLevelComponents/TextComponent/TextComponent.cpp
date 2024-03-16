#include "TextComponent.h"


#include "../../../../CoreSystems/MurphEngine.h"
#include "../PositionComponent/PositionComponent.h"
#include "../../../../LoggingSystem/Logging.h"


//#include <SDL_ttf.h>

//TextComponent::TextComponent()
//    : m_fontSize(12)
//    , m_pTexture(nullptr)
//    , m_TextColor(0, 0, 0, 255) // initialize the text color as black.
//    , m_pTextContents("Default Text")
//{
//    // create a default string to denote that the string needs manually set on initialization.
//    SDL_Color textColor{m_TextColor.red, m_TextColor.green, m_TextColor.green, m_TextColor.alpha};
//    //SDL_Surface* pTextSurface = TTF_RenderText_Solid(m_pFont, m_pTextContents, textColor);
//}

TextComponent::TextComponent(const char* fontLocation, int fontSize, const char* textContents)
    : m_fontSize(fontSize)
    , m_pTexture(nullptr)
    , m_TextColor(0, 0, 0, 255) // initialize the text color as black.
    , m_pTextContents(textContents)
{
    const auto error = TTF_Init();
    if (error != 0)
    {
        const std::string sdlError = SDL_GetError();
        LOG_TO_CONSOLE(kError, "SDL_TTF Initialization Error: " + sdlError);
        return;
    }
    
    m_pFont = MurphEngine::GetInstance()->GetResourceManager()->GetFont(fontLocation, fontSize);
    m_pRenderer = MurphEngine::GetInstance()->GetGraphicsManager()->GetRenderer();

    SetComponentName("TextComponent");

    const SDL_Color textColor(m_TextColor.red, m_TextColor.green, m_TextColor.blue, m_TextColor.alpha);
    SDL_Surface* pTextSurface = TTF_RenderText_Solid(m_pFont, m_pTextContents, textColor);
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTextSurface);

    SDL_FreeSurface(pTextSurface);
}

TextComponent::~TextComponent()
{
    SDL_DestroyTexture(m_pTexture);
}

void TextComponent::Update([[maybe_unused]] double deltaTime)
{
    auto positionComp = static_cast<PositionComponent*>(m_pOwner->GetComponent("PositionComponent"));
    m_textTransform = positionComp->GetRect();

    m_offsetTextTransform = OffsetTextTransformByJustification();

    //TODO

}

void TextComponent::Render() const
{
    int textWidth = 0;
    int textHeight = 0;
    SDL_QueryTexture(m_pTexture, nullptr, nullptr, &textWidth, &textHeight);

    SDL_FRect destRect = { m_offsetTextTransform.GetX(), m_offsetTextTransform.GetY(), static_cast<float>(textWidth), static_cast<float>(textHeight)};
    SDL_RenderCopyF(m_pRenderer, m_pTexture, nullptr, &destRect);
}

void TextComponent::SetText(const char* message)
{
    m_pTextContents = message;
}

void TextComponent::SetTextColor(ColorValues color)
{
    m_TextColor = color;
}

/// <summary>
/// Update displayed Text. Will also update localized string if translation available.
/// </summary>
/// <param name="newText">updated display text</param>
void TextComponent::UpdateText(const char* newText)
{
    const auto translation = MurphEngine::GetInstance()->GetLocalizationManager()->Localize(newText);
    m_pTextContents = translation.c_str();
    SDL_Surface* pTextSurface = TTF_RenderText_Solid(m_pFont, m_pTextContents, SDL_Color{});

    // Create the texture
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTextSurface);

    SDL_FreeSurface(pTextSurface);
}

MurphRect TextComponent::OffsetTextTransformByJustification() const
{
    MurphRect offsetTransform = m_textTransform;

    int textWidth = 0;
    int textHeight = 0;
    SDL_QueryTexture(m_pTexture, nullptr, nullptr, &textWidth, &textHeight);

    const auto rect = static_cast<PositionComponent*>(m_pOwner->GetComponent("PositionComponent"))->GetRect();

    switch (m_justification)
    {
    case textJustification::kTopLeft:
        break;
    case textJustification::kTopCenter:
    {
        offsetTransform.SetX(m_textTransform.GetX() + (m_textTransform.GetWidth() / 2)); // offset the width to center the text.
        break;
    }
    case textJustification::kTopRight: //BUG: will go outside the edge. BAD SOLUTION.
    {
        offsetTransform.SetX(m_textTransform.GetX() + m_textTransform.GetWidth());
        break;
    }
    case textJustification::kCenterLeft:
    {
        offsetTransform.SetY(m_textTransform.GetY() + (m_textTransform.GetHeight() / 2));
        break;
    }
    case textJustification::kCenter:
    {
        auto textXOffset = m_textTransform.GetX() + rect.GetHalfWidth() - (static_cast<float>(textWidth) / 2);
        auto textYOffset = m_textTransform.GetY() + rect.GetHalfHeight() - (static_cast<float>(textHeight) / 2);
        offsetTransform.SetPosition({textXOffset, textYOffset});
        break;
    }
    case textJustification::kCenterRight: //BUG: will go outside the edge. BAD SOLUTION.
    {

        offsetTransform.SetX(m_textTransform.GetX() + m_textTransform.GetWidth());
        offsetTransform.SetY(m_textTransform.GetY() + (m_textTransform.GetHeight() / 2));
        break;
    }
    case textJustification::kBottomLeft:
    {
        offsetTransform.SetY(m_textTransform.GetY() + (m_textTransform.GetHeight()));
        break;
    }
    case textJustification::kBottomCenter:
    {
        offsetTransform.SetX(m_textTransform.GetX() + (m_textTransform.GetWidth() / 2));
        offsetTransform.SetY(m_textTransform.GetY() + m_textTransform.GetHeight());
        break;
    }
    case textJustification::kBottomRight: //BUG: will go outside the edge. BAD SOLUTION.
    {

        offsetTransform.SetX(m_textTransform.GetX() + m_textTransform.GetWidth());
        offsetTransform.SetY(m_textTransform.GetY() + m_textTransform.GetHeight());
        break;
    }
    case textJustification::kError:
    default:
        break;
    }
    return offsetTransform;
}

