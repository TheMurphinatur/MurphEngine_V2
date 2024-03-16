#include "CollisionComponent.h"

#include "../../../../CoreSystems/MurphEngine.h"
#include "../../../../CoreSystems/SceneManager/Scene/Scene.h"
#include "../PositionComponent/PositionComponent.h"


CollisionComponent::CollisionComponent()
    :m_isBlocking(true)
{
    m_componentName = "CollisionComponent";
}

void CollisionComponent::Update([[maybe_unused]]double deltaTime)
{
    //TODO: check for collsions?
}
