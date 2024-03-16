#include "FontManager.h"

#include <ranges>

#include "../Asset Metadata/FontMetadata.h"
#include "Bleach_New/BleachNew.h"


FontManager::~FontManager()
{
    for (const auto& second : m_loadedFonts | std::views::values)
    {
        BLEACH_DELETE(second);
    }
    m_loadedFonts.clear();
}

TTF_Font* FontManager::GetOrLoadFont(const char* filepath, int fontSize)
{
    auto returnVal = GetLoadedFont(filepath, fontSize);
    if (returnVal == nullptr)
        returnVal = AddFontToMap(filepath, fontSize);

    return returnVal;
}


TTF_Font* FontManager::GetLoadedFont(const char* filepath, int fontSize)
{
    for (const auto& [first, second] : m_loadedFonts)
    {
        if (first == filepath)
        {
            if (second->GetFontSize() == fontSize)
            {
                return second->GetFont();
            }
        }
    }
    return nullptr;
}


TTF_Font* FontManager::AddFontToMap(const char* filepath, int fontSize)
{
    FontMetadata* newFont = BLEACH_NEW(FontMetadata(filepath, fontSize));
    const auto emplacedFont = m_loadedFonts.emplace(filepath, newFont);

    return emplacedFont->second->GetFont();
}
