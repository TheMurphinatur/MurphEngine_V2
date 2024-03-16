#include "PositionComponent.h"

PositionComponent::PositionComponent(float xPos, float yPos)
    :m_position(xPos, yPos)
	,m_size(10, 10)
	,m_rect(m_position, m_size)
{
    SetComponentName("PositionComponent");
}

PositionComponent::PositionComponent(float xPos, float yPos, float width, float height)
    :m_position(xPos, yPos)
    ,m_size(width, height)
    ,m_rect(m_position, m_size)
{
    SetComponentName("PositionComponent");
}

/// <summary>
/// Get a Rect of the PositionComponent with Size and Position
/// </summary>
/// <returns> Size and position of this component.</returns>
Rect<float> PositionComponent::GetRect() const
{
    return m_rect;
}

/// <summary>
/// Set Position from top left
/// </summary>
/// <param name="xPos"> Horizontal Position</param>
/// <param name="yPos"> Vertical Position</param>
void PositionComponent::SetPosition(float xPos, float yPos)
{
    m_position.x = xPos;
    m_position.y = yPos;
}

/// <summary>
/// Offset position by input value.
/// </summary>
/// <param name="xPosOffset">how far to move in horizontal direction. -(left) +(right)</param>
/// <param name="yPosOffset">how far to move in vertical direction. -(up) +(down)   </param>
void PositionComponent::UpdatePosition(float xPosOffset, float yPosOffset)
{
    m_position.x += xPosOffset;
    m_position.y += yPosOffset;
}

/// <summary>
/// Update Position Rect with new position and size.
/// </summary>
/// <param name="deltaTime"> delta time</param>
void PositionComponent::Update(double deltaTime)
{
    m_rect.ChangeSize(m_size);
    m_rect.SetPosition(m_position);
    Component::Update(deltaTime);
}
