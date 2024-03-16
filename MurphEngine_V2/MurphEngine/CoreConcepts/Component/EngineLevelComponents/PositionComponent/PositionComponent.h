#pragma once

#include "../../Component.h"

#include "../../../../Math/Rect.h"
#include "../../../../Math/Vector.h"

class PositionComponent final : public Component
{

    MurphLocation m_position;
    MurphSize m_size;
    Rect<float> m_rect;

public:
    PositionComponent(float xPos, float yPos);
    PositionComponent(float xPos, float yPos, float width, float height);

    Rect<float> GetRect() const;

    /**
     * \brief Manually Set position
     * \param xPos new X position
     * \param yPos new Y position
     */
    void SetPosition(float xPos, float yPos);

    /**
     * \brief Offset current position by given values
     * \param xPosOffset offset of current X position
     * \param yPosOffset offset of current Y position
     */
    void UpdatePosition(float xPosOffset = 0, float yPosOffset = 0);

    /**
     * \brief Get position of Component
     * \return Location struct containing X and Y position
     */
    MurphLocation GetPosition() const { return m_position; }

    /// <summary>
    /// Get Size of Component
    /// </summary>
    /// <returns> Horizontal and Vertical size of the component</returns>
    MurphSize GetSize() const { return m_size; }


    virtual void Update([[maybe_unused]] double deltaTime) override;

    
};