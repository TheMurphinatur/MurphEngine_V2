#pragma once
#include "XMLParser.h"


class GraphicsManager;

class WindowParser final:
    public XMLParser
{
public:
    bool ParseWindowFile(GraphicsManager* pGraphics, const char* filepath);
};


