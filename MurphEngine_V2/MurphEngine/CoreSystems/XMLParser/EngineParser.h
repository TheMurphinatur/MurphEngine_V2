#pragma once
#include "XMLParser.h"


class ButtonComponent;

class EngineParser final:
    public XMLParser
{
public:
    virtual bool ParseFile(tinyxml2::XMLElement* element, Entity* pEntity) override;
	void ParseButtonCallback(ButtonComponent* component, const char* callback);
};


