#pragma once
#include <string>
#include <utility>

#include "../Entity/Entity.h"


class Component
{
protected:
    std::string m_componentName = "DefaultComponentName";
    Entity* m_pOwner = nullptr;

public:
    Component();

    virtual ~Component() = default;

    virtual void Initialize() { }
    virtual void Shutdown() { }

    /// <summary>
    /// Set Name of This Component
    /// </summary>
    /// <param name="name"> Component Name</param>
    void SetComponentName(const std::string& name) { m_componentName = name; }

    /// <summary>
    /// Get Name of this component
    /// </summary>
    /// <returns> Component Name</returns>
    std::string GetComponentName() const { return m_componentName; }

    /// <summary>
    /// Assign Owning Entity Object
    /// </summary>
    /// <param name="entity">Entity in which this component is a part of</param>
    void SetOwningEntity(Entity* entity) { m_pOwner = entity; }

    virtual void Update([[maybe_unused]] double deltaTime) { }
    virtual void Render() const { }

protected:

    /// <summary>
    /// Get Entity That this Component is contained within
    /// </summary>
    /// <returns> Owning Object</returns>
    Entity* GetOwningEntity() const { return m_pOwner; }

};
