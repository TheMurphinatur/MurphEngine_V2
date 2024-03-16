#pragma once

#include "../../MurphEngine/CoreConcepts/Component/Component.h"

class CollisionComponent : public Component
{
protected:
    bool m_isBlocking;
    
public:
    CollisionComponent();
    virtual void Update(double deltaTime) override;

    bool IsBlockingCollision() const {return m_isBlocking;}
    void SetBlockingCollision(bool isBlocking) { m_isBlocking = isBlocking;}
};


