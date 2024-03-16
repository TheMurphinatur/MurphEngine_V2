#include "EntityManager.h"

#include <cassert>
#include <ranges>

#include "../../LoggingSystem/Logging.h"
#include "../CoreConcepts/Entity/Entity.h"
#include "Bleach_New/BleachNew.h"
#include "../../CoreConcepts/Component/EngineLevelComponents/ButtonComponent/ButtonComponent.h"
#include "../../CoreConcepts/Component/EngineLevelComponents/ButtonComponent/SliderComponent/SliderComponent.h"
#include "../../CoreConcepts/Component/EngineLevelComponents/ButtonComponent/ToggleComponent/ToggleComponent.h"
#include "../../CoreConcepts/Component/EngineLevelComponents/PositionComponent/PositionComponent.h"

class PositionComponent;

EntityManager::EntityManager() = default;

EntityManager::~EntityManager()
{
    BLEACH_DELETE(m_backgroundEntity);

    BLEACH_DELETE(m_pPlayer);
    for (auto pActor : m_entityMap)
    {
        BLEACH_DELETE(pActor.second);
        pActor.second = nullptr;
    }
    m_entityMap.clear();
    m_currentActorObjectCount = 0;

    for (auto& pInterface : m_widgetEntities)
    {
        BLEACH_DELETE(pInterface.second);
        pInterface.second = nullptr;
    }
    m_widgetEntities.clear();
    m_currentWidgetEntityCount = 0;
}



/**
 * \brief Add player Entity to manager.
 * \return Generated player entity
 */
Entity* EntityManager::AddPlayerEntity()
{
    if (m_pPlayer == nullptr)
        m_pPlayer = BLEACH_NEW(Entity(0));
    else
        LOG_TO_CONSOLE(kWarning, "Player already assigned.");

    return m_pPlayer;
}

/// <summary>
/// Add non player entity
/// </summary> 
/// <returns> Entity Added to manager </returns>
Entity* EntityManager::AddNonPlayerEntity()
{
    //assert(pEntity != nullptr);
    auto newEntity = BLEACH_NEW(Entity(m_currentActorObjectCount));

    auto [iterToEntity, didAddToMap] = m_entityMap.emplace(m_currentActorObjectCount, newEntity);
    if (!didAddToMap)
        LOG_TO_CONSOLE(kWarning, "Entity with key: " + std::to_string(m_currentActorObjectCount) + " already exists. Returning existing entity.");
    m_currentActorObjectCount++;

    return iterToEntity->second;
}

Entity* EntityManager::AddWidgetEntity(const std::string& widgetName)
{
    auto newEntity = BLEACH_NEW(InterfaceEntity(m_currentWidgetEntityCount, widgetName));

    const auto [iterToEntity, didAddToMap] = m_widgetEntities.emplace(m_currentWidgetEntityCount, newEntity);
    if (!didAddToMap)
        LOG_TO_CONSOLE(kWarning, "Entity with key: " + std::to_string(m_currentWidgetEntityCount) + " already exists. Returning existing entity.");
    m_currentWidgetEntityCount++;

    return iterToEntity->second;
}

/// <summary>
/// Add a background to the entity manager  
/// </summary>
/// <returns> Background entity with a sprite component.</returns>
Entity* EntityManager::AddBackgroundEntity()
{
    auto newEntity = BLEACH_NEW(Entity(m_currentActorObjectCount));

    if (m_backgroundEntity != nullptr)
    {
        BLEACH_DELETE(m_backgroundEntity);
        m_backgroundEntity = nullptr;
    }

    m_backgroundEntity = newEntity;

    return m_backgroundEntity;
}

/**
 * \brief Flag engine that we are ready to remove the player entity data.
 */
void EntityManager::InitializeRemovalOfPlayerEntity()
{
    if (m_pPlayer == nullptr)
    {
        LOG_TO_CONSOLE(kWarning, "No player entity to remove.");
        return;
    }
    m_cleanUpPlayerEntity = true;
    LOG_TO_CONSOLE(kSystem, "Player Flagged for cleanup.");
}

/**
 * \brief Flag engine that we are ready to remove the non player entity data for entity with given key.
 * \param key Entity key to remove from map
 */
void EntityManager::InitializeRemovalOfNonPlayerEntity(size_t key)
{
    const auto objectToClear = m_widgetEntities.find(key);
    if (objectToClear == m_widgetEntities.end())
    {
        LOG_TO_CONSOLE(kWarning, "No entity with key: " + std::to_string(key) + " to remove.");
        return;
    }

    m_pEntitiesToDelete.push_back(objectToClear->second);
}

/// <summary>
/// Queue entity for removal
/// </summary>
/// <param name="key"> which entity is to be removed</param>
void EntityManager::InitializeRemovalOfWidgetEntity(size_t key)
{
    const auto objectToClear = m_widgetEntities.find(key);
    if (objectToClear == m_widgetEntities.end())
    {
        LOG_TO_CONSOLE(kWarning, "No entity with key: " + std::to_string(key) + " to remove.");
        return;
    }
    BLEACH_DELETE(objectToClear->second);
    auto var = m_widgetEntities.erase(key);
    //m_pEntitiesToDelete.push_back(objectToClear->second);
}

void EntityManager::ProcessRemovalOfEntities()
{
    for (const auto& entitiesToDelete : m_pEntitiesToDelete)
    {
        BLEACH_DELETE(entitiesToDelete);
    }
    m_pEntitiesToDelete.clear();
}

/// <summary>
/// Search through widgets to find widget with given name
/// </summary>
/// <param name="requestedwidgetName">name of widget</param>
/// <returns> nullptr if no widget found.</returns>
InterfaceEntity* EntityManager::GetWidgetByName(const std::string& requestedwidgetName)
{
	for (const auto& widget : m_widgetEntities | std::views::values)
	{
        if (requestedwidgetName == widget->GetName())
            return widget;
	}

    // no Widget Found.
    LOG_TO_CONSOLE(kWarning, "No widget with name: " + requestedwidgetName + " found.");
	return nullptr;
}

Entity* EntityManager::GetCollidingEntity(const Entity* checkingEntity) const
{
    auto checkingEntityRect = static_cast<PositionComponent*>(checkingEntity->GetComponent("PositionComponent"));
    if (checkingEntityRect == nullptr)
    {
        LOG_TO_CONSOLE(kError, "Checking Entity has no position component to check for collisions.");
        return nullptr;
    }
    MurphRect location = checkingEntityRect->GetRect();

    for (const auto & entityMap : m_entityMap)
    {
        auto collidingEntityRect = static_cast<PositionComponent*>(checkingEntity->GetComponent("PositionComponent"));
        if (collidingEntityRect == nullptr)
        {
            LOG_TO_CONSOLE(kError, "Checked Entity has no position component to check for collisions.");
            return nullptr;
        }
        // if our entity in the map has a collision component.
        if (entityMap.second->GetComponent("CollisionComponent") != nullptr)
        {
            if (location.Intersects(collidingEntityRect->GetRect()))
            {
                return entityMap.second; // return the intersecting entity.
            }
        }
    }

    // there was no colliding entity found. 
    return nullptr;
}

/// <summary>
/// get entitiy of name at position
/// </summary>
/// <param name="name">name of entity we want</param>
/// <param name="position"> position we are checking for entity</param>
/// <returns>entity if it is at requested position</returns>
InterfaceEntity* EntityManager::GetEntityAtPositionWithName(const char* name, const MurphLocation& position)
{
    const auto widget = GetWidgetByName(name);
	if (widget != nullptr)
	{
        const auto checkingPosition = static_cast<PositionComponent*>(widget->GetComponent("PositionComponent"));
        if (checkingPosition != nullptr)
        {
            auto rect = checkingPosition->GetRect();
            if (rect.Contains(position))
            {
                return widget;
            }
        }
	}
	return nullptr;
}

InterfaceEntity* EntityManager::GetEntityAtPositionWithComponent(const char* component, const MurphLocation& position) const
{

    const auto widget = GetEntitiesWithComponentName(component);
    for (const auto interfaceEntity : widget)
    {
	    if (const auto checkingPosition = static_cast<PositionComponent*>(interfaceEntity->GetComponent("PositionComponent")); checkingPosition != nullptr)
        {
	        if (auto rect = checkingPosition->GetRect(); rect.Contains(position))
                return interfaceEntity;
        }
    }
	return nullptr;
}

/// <summary>
/// Get a vector of interface entities that have a component with the given name
/// </summary>
/// <param name="componentName">Which component we are searching for</param>
/// <returns> vector of entities that contain the component requested</returns>
std::vector<InterfaceEntity*> EntityManager::GetEntitiesWithComponentName(const char* componentName) const
{
    std::vector<InterfaceEntity*> entityList;

    for (const auto& widget  : m_widgetEntities | std::views::values)
    {
	    if (widget->GetComponent(componentName) != nullptr)
	    {
            entityList.emplace_back(widget);
	    }
    }

	return entityList;
}

bool EntityManager::IsRequestedMoveBlocked(const Entity* checkingEntity, const MurphRect& requestedRect) const
{
    for (const auto& entity : m_entityMap | std::views::values)
    {
        if (checkingEntity == entity)
        {
            continue;
        }
        // if our entity in the map has a collision component.
        if (entity->GetComponent("CollisionComponent") != nullptr)
        {
            auto rectToCheck = static_cast<PositionComponent*>(entity->GetComponent("PositionComponent"))->GetRect(); // we get a position component.
            if (rectToCheck.Intersects(requestedRect)) // we check if the entity's position intersects
            {
                return true;
            }
        }
    }
    return false;
}


void EntityManager::Update(double deltaTime)
{
    if (m_backgroundEntity != nullptr)
        m_backgroundEntity->Update(deltaTime);

    if (m_pPlayer != nullptr)
        m_pPlayer->Update(deltaTime);

    for (const auto& val : m_entityMap | std::views::values)
        val->Update(deltaTime);

    // interface is on top of the rest of the stuff.
    for (const auto& val : m_widgetEntities | std::views::values)
        val->Update(deltaTime);

    ProcessRemovalOfEntities();

}

void EntityManager::UpdatePlayerEntityOnly(double deltaTime) const
{
    if (m_pPlayer != nullptr)
        m_pPlayer->Update(deltaTime);
}

void EntityManager::UpdateNonPlayerEntitiesOnly(double deltaTime) const
{
    for (auto val : m_entityMap | std::views::values)
    {
        if (val != nullptr)
            val->Update(deltaTime);
    }
}


void EntityManager::UpdateWidgetEntities(double deltaTime) const
{
    for (const auto val : m_widgetEntities | std::views::values)
    {
        if (val != nullptr)
            val->Update(deltaTime);
    }
}


void EntityManager::CheckWidgetsForButtonHighlight(float x, float y) const
{
    for (const auto& val : m_widgetEntities | std::views::values)
        auto dummyVal = val->CheckWidgetForHighlight(x, y);
}

void EntityManager::CheckWidgetsForButtonClick(float x, float y) const
{
    for (const auto& val : m_widgetEntities | std::views::values)
    {
	    if (val->CheckWidgetForHighlight(x, y))
	    {
			val->CheckWidgetForClick(x, y);
	    }
    }
}

/// <summary>
/// Render Managed Entities
/// </summary>
void EntityManager::Render() const
{
    // render background.
    if (m_backgroundEntity != nullptr)
        m_backgroundEntity->Render();

    // render player
    if (m_pPlayer != nullptr)
        m_pPlayer->Render();

    // render all non player entities.
    for (const auto& val : m_entityMap | std::views::values)
        val->Render();

    // interface is on top of the rest of the stuff.
    for (const auto& val : m_widgetEntities | std::views::values)
        val->Render();
}

/// <summary>
/// render player only
/// </summary>
void EntityManager::RenderPlayerEntityOnly() const
{
    assert(m_pPlayer != nullptr);
    m_pPlayer->Render();
}

/// <summary>
/// render NPC only
/// </summary>
void EntityManager::RenderNonPlayerEntitiesOnly() const
{
    for (const auto& entity : m_entityMap | std::views::values)
        entity->Render();
}

/// <summary>
/// Re-assign player entity. 
/// </summary>
/// <param name="newPlayer"> new entity</param>
/// <returns> new player</returns>
Entity* EntityManager::ReAssignPlayerEntity(Entity* newPlayer)
{
    // make sure we have a player entity to reassign, and we aren't just replacing it with itself.
    if (m_pPlayer == nullptr)
        return nullptr;
    if (m_pPlayer == newPlayer)
        return m_pPlayer;

    // assign new player entity.
    m_pPlayer = newPlayer;

    LOG_TO_CONSOLE(kSystem, "Player re-assigned successfully.");
    return m_pPlayer;
}
