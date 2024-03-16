#pragma once


#include "../../Component.h"
#include "../../../Color/ColorValues.h"
#include "../../../../Middleware/SDL2/include/SDL_ttf.h"


#include "../../../../Math/Rect.h"


class TextComponent : public Component
{
protected:
    enum class textJustification
    {
        kTopLeft,
        kTopCenter,
        kTopRight,
        kCenterLeft,
        kCenter,
        kCenterRight,
        kBottomLeft,
        kBottomCenter,
        kBottomRight,

        kError
    };
    // private variables.

    //MurphLocation m_textPos = {0.f,0.f};
    TTF_Font* m_pFont = nullptr;
    int m_fontSize;
    SDL_Texture* m_pTexture;
    SDL_Renderer* m_pRenderer = nullptr;
    MurphRect m_textTransform;
    MurphRect m_offsetTextTransform;

    textJustification m_justification = textJustification::kCenter;

    ColorValues m_TextColor;
    const char* m_pTextContents;


public:
    //TextComponent();
    TextComponent(const char* fontLocation, int fontSize, const char* textContents);
    virtual ~TextComponent() override;
    virtual void Update([[maybe_unused]] double deltaTime) override;
    virtual void Render() const override;
    void SetText(const char* message);
    void SetTextColor(ColorValues color);
    void SetParentPos(MurphRect parentPosition) { m_textTransform = parentPosition; }

    void UpdateText(const char* newText);
protected:
    MurphRect OffsetTextTransformByJustification() const;

};


