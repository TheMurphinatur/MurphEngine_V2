#include "FontMetadata.h"

FontMetadata::FontMetadata(const char* path, int fontSize)
    :m_filePath(path)
    ,m_fontSize(fontSize)
{
    SetFont(m_filePath, m_fontSize);
}

void FontMetadata::SetFont(const char* path, int fontSize)
{
    m_filePath = path;
    m_fontSize = fontSize;
    m_pFont = TTF_OpenFont(m_filePath, m_fontSize);
}

void FontMetadata::ClearFont()
{
    TTF_CloseFont(m_pFont);
    m_pFont = nullptr;
}
