#pragma once


#include "../../Middleware/SDL2/include/SDL_ttf.h"

#include "FontManager/FontManager.h"
#include "SpriteManager/TextureManager.h"

class ResourceManager
{
    TextureManager m_textureManager;
    FontManager m_fontManager;

public:
    ResourceManager();
    ~ResourceManager() = default;

    SDL_Texture* GetImage(const char* filepath);
    TTF_Font* GetFont(const char* filepath, int fontSize);
};
