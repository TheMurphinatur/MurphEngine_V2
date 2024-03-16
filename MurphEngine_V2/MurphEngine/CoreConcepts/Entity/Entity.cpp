#include "Entity.h"

#include <cassert>
#include <ranges>

#include "Bleach_New/BleachNew.h"
#include "../CoreConcepts/Component/Component.h"
#include "../../LoggingSystem/Logging.h"

Entity::Entity(size_t key)
    :m_actorKey(key)
{

}

Entity::Entity()
{
    m_actorKey = 0;
}

Entity::~Entity()
{
    // delete all components
    for (auto& val : m_components | std::views::values)
    {
        BLEACH_DELETE(val);
        val = nullptr;
        assert(val == nullptr);
    }
    // clear the map and assert it is empty
    m_components.clear();
    assert(m_components.empty());
}

/**
 * \brief Attempt to retrieve a component from the entity.
 * \param componentName Requested Component string name
 * \return requested component if found, nullptr if not found
 */
Component* Entity::GetComponent(const std::string& componentName) const
{
    if (m_components.empty())
    {
        LOG_TO_CONSOLE(kError, "Component list is empty.");
        return nullptr;
    }

    //find the requested component
    const auto foundVal = m_components.find(componentName);

    //if we found the requested component
    if (foundVal != m_components.end())
        return foundVal->second;

    // we did not find the requested component
    return nullptr;
}

/**
 * \brief Add component to entity.
 * \param component Component to add to entity
 * \return Added component.
 */
Component* Entity::AddComponent(Component* component)
{
    // we attempt to insert the component into the map.
    const auto insertionAttempt = m_components.emplace(component->GetComponentName(), component);

    if (insertionAttempt != m_components.end())
    {
        insertionAttempt->second->SetOwningEntity(this);
    }

    return insertionAttempt->second;
}

/**
 * \brief Update All components in entity.
 * \param deltaTime delta time
 */
void Entity::Update(double deltaTime)
{
    for (const auto& val : m_components | std::views::values)
    {
        //if (val != nullptr)
        val->Update(deltaTime);
    }
}

/// <summary>
/// Render all components that have an overloaded render function.
/// </summary>
void Entity::Render()
{
    for (const auto& val : m_components | std::views::values)
    {
        if (val != nullptr)
            val->Render();
    }
}
