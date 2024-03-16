#pragma once
#include "../../../Middleware/SDL2/include/SDL_ttf.h"
#include <unordered_map>

class FontMetadata;

class FontManager
{

private:
    std::unordered_multimap<const char*, FontMetadata*> m_loadedFonts;

public:

    FontManager() = default;
    ~FontManager();

    TTF_Font* GetOrLoadFont(const char* filepath, int fontSize);

private:
    TTF_Font* GetLoadedFont(const char* filepath, int fontSize);
    TTF_Font* AddFontToMap(const char* filepath, int fontSize);

};
