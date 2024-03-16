#pragma once

#include "../Entity.h"


class ButtonComponent;

class InterfaceEntity final: public Entity
{
    std::string m_interfaceEntityName;

public:
    InterfaceEntity();
    InterfaceEntity(size_t index);
    InterfaceEntity(size_t index, std::string name);


    std::string GetName() const { return m_interfaceEntityName; }
    void SetName(const std::string& newName) { m_interfaceEntityName = newName; }

    bool CheckWidgetForHighlight(float x, float y) const;
    void CheckWidgetForClick(float x, float y) const;

    ButtonComponent* GetWidgetByName(const std::string& name) const;
};
