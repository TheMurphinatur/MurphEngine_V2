#include "SpriteMetadata.h"

#include <SDL_render.h> 

void SpriteMetadata::ClearTexture()
{
    SDL_DestroyTexture(m_pTexture);
    m_pTexture = nullptr;
}
