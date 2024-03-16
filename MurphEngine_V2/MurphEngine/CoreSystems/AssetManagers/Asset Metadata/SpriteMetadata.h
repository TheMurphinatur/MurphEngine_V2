#pragma once
#include "MetadataBase.h"

struct SDL_Texture;


class SpriteMetadata final: public ResourceMetaData
{
    SDL_Texture* m_pTexture = nullptr;
public:
    SDL_Texture* GetTexture() const { return m_pTexture; }
    void SetTexture(SDL_Texture* texture) { m_pTexture = texture; }
    void ClearTexture();
};



