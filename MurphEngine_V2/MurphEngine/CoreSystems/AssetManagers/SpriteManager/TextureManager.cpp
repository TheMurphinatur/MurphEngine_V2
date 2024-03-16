#include "TextureManager.h"

#include <ranges>

#include "../ResourceManager.h"
#include "../../MurphEngine.h"

#include "../../../LoggingSystem/Logging.h"
#include "../Asset Metadata/SpriteMetadata.h"
#include "Bleach_New/BleachNew.h"

TextureManager::TextureManager(ResourceManager* pManager)
    : m_pResourceManager(pManager)
{
}

TextureManager::~TextureManager()
{
    if (m_loadedTexturesWithMetaData.empty())
    {
        return;
    }

    for (const auto& pTextureData : m_loadedTexturesWithMetaData | std::views::values)
    {
        pTextureData->ClearTexture();
        BLEACH_DELETE(pTextureData);
    }

    m_loadedTexturesWithMetaData.clear();
}

SDL_Texture* TextureManager::GetOrLoadImage(const char* filepath)
{
    if (IsFileLoaded(filepath))
    {
        auto& data = m_loadedTexturesWithMetaData.at(filepath);

        if (data->GetCacheStatus() == CacheStatus::kCached)
        {
            LOG_TO_CONSOLE(kDebug, "Loading cached Image from Map.");
        }
        return data->GetTexture();
    }

    return AddFileToMap(filepath);
}

bool TextureManager::IsFileLoaded(const char* filepath)
{
    if (auto search = m_loadedTexturesWithMetaData.find(filepath); search != m_loadedTexturesWithMetaData.end())
        return true;

    return false;
}

SDL_Texture* TextureManager::AddFileToMap(const char* filepath)
{
    SDL_Texture* loadedTexture = MurphEngine::GetInstance()->GetGraphicsManager()->LoadTexture(filepath);
    auto pLocalData = BLEACH_NEW(SpriteMetadata());
    pLocalData->SetTexture(loadedTexture);
    pLocalData->IncrementRefCount();
    pLocalData->SetCacheStatus(CacheStatus::kCaching);

    const auto [iterator2, success2] = m_loadedTexturesWithMetaData.emplace(filepath, pLocalData);

    if (!success2)
    {
        LOG_TO_CONSOLE(kDebug, "Image Insertion into map failed!");

        return nullptr;
    }
    return iterator2->second->GetTexture();
}
