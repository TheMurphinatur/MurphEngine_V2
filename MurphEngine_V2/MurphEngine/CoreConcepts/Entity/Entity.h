#pragma once
#include <string>
#include <unordered_map>

class Component;

class Entity
{
protected:
    // This is the key for the entity. This is used to identify the entity in the entity manager.
    size_t m_actorKey = 0;

    // This contains our components we are using for this entity.
    std::unordered_multimap<std::string, Component*> m_components;

public:
    Entity(size_t key);
    Entity();
    virtual ~Entity();

    Component* GetComponent(const std::string& componentName) const;

    auto GetComponentsOfName(const std::string& componentName) const{ return m_components.equal_range(componentName); }

    Component* AddComponent(Component* component);

    // This is the key access for the entity. This is used to identify the entity in the entity manager.
    void SetActorKey(size_t key) { m_actorKey = key; }
    size_t GetActorKey() const { return m_actorKey; }

    virtual void Update([[maybe_unused]]double deltaTime);

    virtual void Render();
};
