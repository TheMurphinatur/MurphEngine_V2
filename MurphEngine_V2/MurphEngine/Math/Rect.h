#pragma once

#include "Vector.h"



template <typename TypeName>
class Rect
{
    Vector2<TypeName> m_position;
    Vector2<TypeName> m_size;

public:
    Rect() = default;

    Rect(TypeName x, TypeName y, TypeName width, TypeName height)
        : m_position(x, y)
        , m_size(width, height)
    {

    }

    Rect(Vector2<float> position, Vector2<float> size)
        : m_position(position)
        , m_size(size)
    {

    }

    // Getters

    [[nodiscard]] TypeName GetX() const { return m_position.x; }
    [[nodiscard]] TypeName GetY() const { return m_position.y; }
    [[nodiscard]] TypeName GetWidth() const { return m_size.x; }
    [[nodiscard]] TypeName GetHalfWidth() const { return m_size.x / 2; }
    [[nodiscard]] TypeName GetHeight() const { return m_size.y; }
    [[nodiscard]] TypeName GetHalfHeight() const { return m_size.y / 2; }
    [[nodiscard]] Vector2<TypeName> GetPosition() const { return m_position; }
    [[nodiscard]] Vector2<TypeName> GetSize() const { return m_size; }

    // Setters

    void SetX(TypeName newX) { m_position.x = newX; }
    void SetY(TypeName newY) { m_position.y = newY; }
    void SetWidth(TypeName newWidth) { m_size.x = newWidth; }
    void SetHeight(TypeName newHeight) { m_size.y = newHeight; }
    void SetPosition(Vector2<TypeName> position) { m_position = position; }
    void SetSize(Vector2<TypeName> size) { m_size = size; }

    // offset
    void OffsetX(TypeName offset) { m_position.x += offset; }
    void OffsetY(TypeName offset) { m_position.y += offset; }

    // Additional Getters
    [[nodiscard]] TypeName GetTop() const { return m_position.y; }
    [[nodiscard]] TypeName GetBottom() const { return m_position.y + m_size.y; }
    [[nodiscard]] TypeName GetLeftLimit() const { return m_position.x; }
    [[nodiscard]] TypeName GetRightLimit() const { return m_position.x + m_size.x; }
    [[nodiscard]] Vector2<TypeName> GetCenterPoint() const
    {
        TypeName centerX = m_position.x + GetHalfWidth();
        TypeName centerY = m_position.y + GetHalfHeight();

        return Vector2<TypeName>(centerX, centerY);
    }


    bool operator==(const Rect& other) const
    {
        return m_position == other.m_position && m_size == other.m_size;
    }

    void MoveTo(const Vector2<TypeName>& newPosition)
    {
        m_position = newPosition;
    }

    void ChangeSize(const Vector2<TypeName>& newSize)
    {
        m_size = newSize;
    }

    [[nodiscard]] bool Contains(const Vector2<TypeName>& point)
    {
        return (point.x >= m_position.x && point.x < m_position.x + m_size.x) &&
               (point.y >= m_position.y && point.y < m_position.y + m_size.y);
    }

    [[nodiscard]] bool Intersects(const Rect<TypeName>& other)
    {
        return (m_position.x < other.m_position.x + other.m_size.x) &&
               (m_position.x + m_size.x > other.m_position.x) &&
               (m_position.y < other.m_position.y + other.m_size.y) &&
               (m_position.y + m_size.y > other.m_position.y);
    }
};

using MurphRect = Rect<float>;