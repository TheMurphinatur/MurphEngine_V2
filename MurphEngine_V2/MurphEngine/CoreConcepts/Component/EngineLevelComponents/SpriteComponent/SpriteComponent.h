#pragma once
#include <string>

#include "../../Component.h"
#include "../../../../CoreConcepts/Color/ColorValues.h"
#include "../../../../Math/Rect.h"
#include "../../../../Middleware/SDL2/include/SDL_image.h"
#include "../../../../Middleware/SDL2/include/SDL_render.h"

class SpriteComponent : public Component
{
protected:
    std::string m_pSpriteLocation;
    MurphRect m_spriteTransform;
    ColorValues m_spriteColor;
    SDL_Texture* m_pSpriteTexture;

public:
    SpriteComponent();
    SpriteComponent(float width, float height);
    virtual ~SpriteComponent() override;


    bool AddTexture(const char* imageLocation);
    virtual void Update([[maybe_unused]] double deltaTime) override;
    virtual void Render() const override;
    void SetSpriteSize(float width, float height);
    void SetSpritePosition(float x, float y);

    void SetSpriteColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

    float GetSpriteWidth() const { return m_spriteTransform.GetWidth(); }
    float GetSpriteHeight() const { return m_spriteTransform.GetHeight(); }

    float GetSpriteX() const { return m_spriteTransform.GetX(); }
    float GetSpriteY() const { return m_spriteTransform.GetY(); }
    
    void SetTexture(SDL_Texture* texture) { m_pSpriteTexture = texture; }
};




