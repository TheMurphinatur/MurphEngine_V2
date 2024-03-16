#pragma once
#include "MetadataBase.h"
#include "../FontManager/FontManager.h"



class FontMetadata final: public ResourceMetaData
{
    TTF_Font* m_pFont = nullptr;
    const char* m_filePath = nullptr;
    int m_fontSize = 0;
public:
    FontMetadata(const char* path, int fontSize);

    TTF_Font* GetFont() const { return m_pFont; }
    void SetFont(const char* path, int fontSize);
    void ClearFont();
    int GetFontSize() const { return m_fontSize; }
    const char* GetFilePath() const { return m_filePath; }
};



