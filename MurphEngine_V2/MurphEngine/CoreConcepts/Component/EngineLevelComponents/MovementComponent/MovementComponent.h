#pragma once


#include "../../../../Math/Vector.h"

#include "../../Component.h"

class MovementComponent : public Component
{
protected:
    float m_movementSpeed;

    Vector2<float> m_movementDirection;
    
public:
    MovementComponent();
    virtual void Update(double deltaTime) override;

    void SetMovementSpeed(float newSpeed) { m_movementSpeed = newSpeed; }
    float GetMovementSpeed() const { return m_movementSpeed; }

    void SetMovementDirection(float x, float y) { m_movementDirection = { x, y }; }
    Vector2<float> GetMovementDirection() const { return m_movementDirection; }
};


