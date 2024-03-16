#include "XMLParser.h"

#include "../EntityManager/EntityManager.h"
#include "../../LoggingSystem/Logging.h"


bool XMLParser::ParseFile([[maybe_unused]]const char* filepath)
{
    LOG_TO_CONSOLE(kError, "Overload this function.");
    return false;
}

bool XMLParser::ParseFile([[maybe_unused]] const tinyxml2::XMLDocument& document)
{
    LOG_TO_CONSOLE(kError, "Overload this function.");
    return false;
}

bool XMLParser::ParseElementForComponents(tinyxml2::XMLElement* element, Entity* pEntity)
{
    return ParseFile(element, pEntity);
}

bool XMLParser::ParseFile([[maybe_unused]] tinyxml2::XMLElement* element, [[maybe_unused]] Entity* pEntity)
{
    LOG_TO_CONSOLE(kError, "Overload this function.");
    return false;
}
