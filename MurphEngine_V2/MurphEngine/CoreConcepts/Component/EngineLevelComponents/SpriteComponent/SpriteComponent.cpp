#include "SpriteComponent.h"

#include <cassert>

#include "../../../../CoreSystems/MurphEngine.h"
#include "../PositionComponent/PositionComponent.h"
#include "../../../../LoggingSystem/Logging.h"


class PositionComponent;
/**
 * \brief Create Default Sprite Component with a default size of 10x10
 */
SpriteComponent::SpriteComponent()
    :m_spriteTransform{0, 0, 10, 10}
    ,m_spriteColor(50, 50, 50 ,255)
    ,m_pSpriteTexture(nullptr)

{
    SetComponentName("SpriteComponent");
}

SpriteComponent::SpriteComponent(float width, float height)
    :m_spriteTransform{ 0, 0, width, height }
    , m_spriteColor(50, 50, 50, 255)
    , m_pSpriteTexture(nullptr)

{
    SetComponentName("SpriteComponent");
}


SpriteComponent::~SpriteComponent()
{
    //
}

/**
 * \brief Set sprite position for rendering
 * \param x set sprite X position
 * \param y set sprite Y position
 */
void SpriteComponent::SetSpritePosition(float x, float y)
{
    m_spriteTransform.SetPosition({ x, y });
}

/**
 * \brief set sprite size
 * \param width width of sprite
 * \param height height of sprite
 */
void SpriteComponent::SetSpriteSize(float width, float height)
{
    m_spriteTransform.SetSize({ width, height });
}


/**
 * \brief Render Sprite to screen. If Texture is not set, render a rectangle.
 */
void SpriteComponent::Render() const
{

    auto debug = m_pSpriteLocation;
    const auto var = MurphEngine::GetInstance()->GetGraphicsManager();
    SDL_FRect sdlRect(m_spriteTransform.GetX(), m_spriteTransform.GetY(), m_spriteTransform.GetWidth(), m_spriteTransform.GetHeight());
    
    // if we have a texture, render it.
    if (m_pSpriteTexture != nullptr)
    {
        assert(m_pSpriteTexture != nullptr);
        SDL_RenderCopyF(var->GetRenderer(), m_pSpriteTexture, nullptr, &sdlRect);
        return;
    }
    // otherwise, render a rectangle.
    var->SetDrawColor(m_spriteColor.red, m_spriteColor.green, m_spriteColor.blue, m_spriteColor.alpha);
    SDL_RenderFillRectF(var->GetRenderer(), &sdlRect);
}

/**
 * \brief Add Texture to Sprite
 * \param imageLocation Filepath to image
 * \return true if loaded successfully, false otherwise.
 */
bool SpriteComponent::AddTexture(const char* imageLocation)
{
    m_pSpriteLocation = imageLocation;
    m_pSpriteTexture = MurphEngine::GetInstance()->GetResourceManager()->GetImage(m_pSpriteLocation.c_str());

    return false;
}

/**
 * \brief Update Sprite Position
 * \param deltaTime delta time
 */
void SpriteComponent::Update([[maybe_unused]] double deltaTime)
{
    // update the position of our sprite based on the position component of the entity.
    const auto pOwner = GetOwningEntity();
    if (pOwner == nullptr)
        LOG_TO_CONSOLE(kError, "Unable to find position component for sprite component update. No position updated.");
    else
    {
        const auto test = pOwner->GetComponentsOfName("PositionComponent");
        for (auto iter = test.first; iter != test.second; ++iter)
        {
            const auto positionComponent = static_cast<PositionComponent*>(iter->second);
            const auto position = positionComponent->GetPosition();
            SetSpritePosition(position.x, position.y);
            const auto size = positionComponent->GetSize();
            SetSpriteSize(size.x, size.y);
        }
    }

}

/**
 * \brief set sprite color if no texture is set.
 * \param red red value
 * \param green green value
 * \param blue blue value
 * \param alpha alpha
 */
void SpriteComponent::SetSpriteColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    m_spriteColor.red = red;
    m_spriteColor.green = green;
    m_spriteColor.blue = blue;
    m_spriteColor.alpha = alpha;
}
