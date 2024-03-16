#include "ResourceManager.h"

#include "../MurphEngine.h"
#include "../AssetManagers/SpriteManager/TextureManager.h"


ResourceManager::ResourceManager()
    : m_textureManager(this)
{
}

/// <summary>
/// Get a Texture based on filepath
/// </summary>
/// <param name="filepath">filepath of the image we want</param>
/// <returns>SDL_Texture based on requested filepath</returns>
SDL_Texture* ResourceManager::GetImage(const char* filepath)
{
    return m_textureManager.GetOrLoadImage(filepath);
}

/// <summary>
/// Get a font based on filepath and fontSize
/// </summary>
/// <param name="filepath"> filepath of the font to load</param>
/// <param name="fontSize"> how big is the font</param>
/// <returns> TTF_Font based on input values</returns>
TTF_Font* ResourceManager::GetFont(const char* filepath, int fontSize)
{
    return m_fontManager.GetOrLoadFont(filepath, fontSize);
}
