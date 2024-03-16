#pragma once



#include "../../Middleware/tinyXML2/include/tinyxml2.h"

class Entity;
class EntityManager;


class XMLParser
{
protected:
    tinyxml2::XMLDocument m_parserDoc;
    EntityManager* m_pManager = nullptr;

public:
    XMLParser() = default;
    virtual ~XMLParser() = default;

    virtual bool ParseFile(const char* filepath);
    virtual bool ParseFile(const tinyxml2::XMLDocument& document);

    virtual bool ParseElementForComponents(tinyxml2::XMLElement* element, Entity* pEntity);
    virtual bool ParseFile(tinyxml2::XMLElement* element, Entity* pEntity);
};



