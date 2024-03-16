#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "../../CoreConcepts/Entity/InterfaceEntity/InterfaceEntity.h"
#include "../../Math/Rect.h"

class ButtonComponent;
class Entity;

class EntityManager
{
    bool m_cleanUpPlayerEntity = false;

    Entity* m_pPlayer = nullptr;
    Entity* m_backgroundEntity = nullptr; // i would prefer this to be somewhere else maybe? allow for rolling backgrounds.

    std::unordered_map<size_t, Entity*> m_entityMap;
    std::unordered_map<size_t, InterfaceEntity*> m_widgetEntities;

    std::vector<Entity*> m_pEntitiesToDelete;

    size_t m_currentActorObjectCount = 0;
    size_t m_currentWidgetEntityCount = 0;

public:
    EntityManager();
    ~EntityManager();

    // Entity Getting functions.
    Entity* GetPlayer() const { return m_pPlayer; }
    Entity* GetEntity(size_t key) const { return m_entityMap.at(key); }

    // Entity Adding functions.
    Entity* AddPlayerEntity();
    Entity* AddNonPlayerEntity();
    Entity* AddWidgetEntity(const std::string& widgetName);
    Entity* AddBackgroundEntity();

    // Entity Removal functions.
    void InitializeRemovalOfPlayerEntity();
    void InitializeRemovalOfNonPlayerEntity(size_t key);
    void InitializeRemovalOfWidgetEntity(size_t key);

    void ProcessRemovalOfEntities();

    // Entity Event Functions
    void SendMessage([[maybe_unused]] const std::string& message) { }

    InterfaceEntity* GetWidgetByName(const std::string& requestedwidgetName);

    Entity* GetCollidingEntity(const Entity* checkingEntity) const;

    InterfaceEntity* GetEntityAtPositionWithName(const char* name, const MurphLocation& position);

    InterfaceEntity* GetEntityAtPositionWithComponent(const char* component, const MurphLocation& position) const;

    std::vector<InterfaceEntity*> GetEntitiesWithComponentName(const char* componentName) const;

    bool IsRequestedMoveBlocked(const Entity* checkingEntity, const MurphRect& requestedRect) const;

    // Entity Update functions.
    void Update([[maybe_unused]] double deltaTime);
    void UpdatePlayerEntityOnly([[maybe_unused]] double deltaTime) const;
    void UpdateNonPlayerEntitiesOnly([[maybe_unused]] double deltaTime) const;
    void UpdateWidgetEntities([[maybe_unused]] double deltaTime) const;

    void CheckWidgetsForButtonHighlight(float x, float y) const;
    void CheckWidgetsForButtonClick(float x, float y) const;

    // Entity Render functions.
    void Render() const;


	void RenderPlayerEntityOnly() const;
    void RenderNonPlayerEntitiesOnly() const;

    Entity* ReAssignPlayerEntity(Entity* newPlayer);
private:
};
