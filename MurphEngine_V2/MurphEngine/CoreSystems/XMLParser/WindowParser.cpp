#include "WindowParser.h"

#include <string>
#include "../MurphEngine.h"


bool WindowParser::ParseWindowFile(GraphicsManager* pGraphics, const char* filepath)
{
    tinyxml2::XMLDocument parserDoc;

    if (const auto error = parserDoc.LoadFile(filepath); error != 0)
    {
        LOG_TO_CONSOLE(kError, "Error Reading file");
        return false;
    }

    tinyxml2::XMLElement* rootElement = parserDoc.RootElement();


    if (!rootElement || strcmp(rootElement->Name(), "WindowSetup") != 0)
    {
        LOG_TO_CONSOLE(kError, "either not the root element, or the window tag is wrong.");
        return false;
    }
    const char* windowTitle = "default";
    int windowStartX = 1000;
    int windowStartY = 1000;
    int windowWidth = 100;
    int windowHeight = 100;

    auto currentElement = rootElement->FirstChildElement("Window");

    // iterate through window settings.
    for (tinyxml2::XMLElement* windowElement = currentElement->FirstChildElement();
        windowElement != nullptr;
        windowElement = windowElement->NextSiblingElement())
    {
        const auto elementName = windowElement->Name();

        if (std::strcmp(elementName, "WindowTitle") == 0)
        {
            windowTitle = windowElement->Attribute("title");
        }
        else if (std::strcmp(elementName, "StartLocation") == 0)
        {
            windowStartX = std::atoi(windowElement->Attribute("x"));
            windowStartY = std::atoi(windowElement->Attribute("y"));
        }
        else if (std::strcmp(elementName, "WindowSize") == 0)
        {
            windowWidth = std::atoi(windowElement->Attribute("width"));
            windowHeight = std::atoi(windowElement->Attribute("height"));
        }
    }

    pGraphics->CreateNewWindow(windowTitle, windowStartX, windowStartY, windowWidth, windowHeight);
    LOG_TO_CONSOLE(kSystem, "Window Parsed Successfully.");
    return true;
}
