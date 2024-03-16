#pragma once

#include <unordered_map>

class ResourceMetaData;
class ResourceManager;
class SpriteMetadata;

struct SDL_Texture;


class TextureManager
{
    ResourceManager* m_pResourceManager;
    std::unordered_map<const char*, SpriteMetadata*> m_loadedTexturesWithMetaData;

public:
    TextureManager(ResourceManager* pManager);
    ~TextureManager();
    SDL_Texture* GetOrLoadImage(const char* filepath);

private:
    bool IsFileLoaded(const char* filepath);
    SDL_Texture* AddFileToMap(const char* filepath);

};
