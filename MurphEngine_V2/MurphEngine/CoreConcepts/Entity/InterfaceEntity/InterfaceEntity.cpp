#include "InterfaceEntity.h"

#include <ranges>

#include "../../Component/EngineLevelComponents/ButtonComponent/SliderComponent/SliderComponent.h"
#include "../CoreConcepts/Component/EngineLevelComponents/ButtonComponent/ButtonComponent.h"

InterfaceEntity::InterfaceEntity(size_t index)
    :Entity(index)
{
    m_interfaceEntityName = "Default";
}

InterfaceEntity::InterfaceEntity(size_t index, std::string name)
    :Entity(index)
    ,m_interfaceEntityName(std::move(name))
{
    //
}

InterfaceEntity::InterfaceEntity()
{
    m_interfaceEntityName = "Default";
}

bool InterfaceEntity::CheckWidgetForHighlight(const float x, const float y) const
{
    for (const auto& component : m_components | std::views::values)
    {
	    if (const auto buttonComponent = dynamic_cast<ButtonComponent*>(component); buttonComponent != nullptr)
			return buttonComponent->IsHighlighted(x, y);
    }
    return false;
}

void InterfaceEntity::CheckWidgetForClick(const float x, const float y) const
{
    for (const auto& component : m_components | std::views::values)
    {
	    if (const auto buttonComponent = dynamic_cast<ButtonComponent*>(component); buttonComponent != nullptr && buttonComponent->IsHighlighted(x, y))
        {
	        if (const auto sliderComponent = dynamic_cast<SliderComponent*>(buttonComponent); sliderComponent != nullptr)
	    		sliderComponent->SetKnobPosition(x); // if we are a slider, we will update the position (if within the bar)

            buttonComponent->TriggerButton();
            return;
        }
    }
}

ButtonComponent* InterfaceEntity::GetWidgetByName(const std::string& name) const
{
    for (const auto& widgetComponent : m_components | std::views::values)
    {
        const auto buttonComponent = static_cast<ButtonComponent*>(widgetComponent);
        if (buttonComponent == nullptr)
            continue;
        if (buttonComponent->GetName() == name)
            return buttonComponent;
    }
    return nullptr;
}
