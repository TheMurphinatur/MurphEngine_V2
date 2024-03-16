#include "MovementComponent.h"

#include "../../../../CoreSystems/MurphEngine.h"
#include "../../../../CoreSystems/SceneManager/Scene/Scene.h"
#include "../PositionComponent/PositionComponent.h"


MovementComponent::MovementComponent()
    : m_movementSpeed(1.0f)
    , m_movementDirection(0, 0)
{
    m_componentName = "MovementComponent";
}

void MovementComponent::Update(double deltaTime)
{
    const auto position = static_cast<PositionComponent*>(m_pOwner->GetComponent("PositionComponent"));
    const auto inputManager = MurphEngine::GetInstance()->GetInputManager();
    const auto graphicsManager = MurphEngine::GetInstance()->GetGraphicsManager();

    const float maxWidthPosition = static_cast<float>(graphicsManager->GetWindowWidth()) - position->GetSize().x;
    const float maxHeightPosition = static_cast<float>(graphicsManager->GetWindowHeight()) - position->GetSize().y;

    if (inputManager->IsKeyPressed(InputManager::MurphKey_w) && position->GetPosition().y > 0.f)
        m_movementDirection.y = -1.0f;
    else if (inputManager->IsKeyPressed(InputManager::MurphKey_s) && position->GetPosition().y < maxHeightPosition)
        m_movementDirection.y = 1.0f;
    if (inputManager->IsKeyPressed(InputManager::MurphKey_a) && position->GetPosition().x > 0.f)
        m_movementDirection.x = -1.0f;
    else if (inputManager->IsKeyPressed(InputManager::MurphKey_d) && position->GetPosition().x < maxWidthPosition)
        m_movementDirection.x = 1.0f;
    else
    {
        m_movementDirection.x = 0.f;
        m_movementDirection.y = 0.f;
    }
    const auto xPositionOffset = m_movementDirection.x * static_cast<float>(m_movementSpeed * deltaTime);
    const auto yPositionOffset = m_movementDirection.y * static_cast<float>(m_movementSpeed * deltaTime);

    position->UpdatePosition(xPositionOffset, yPositionOffset);
}
