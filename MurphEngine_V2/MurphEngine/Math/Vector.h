#pragma once
#include <cassert>
#include <type_traits>
#include <cmath>

#include "Math.h"

//template<class Type>
//concept Number = std::is_arithmetic_v<Type>;

template <Number Type>
struct Vector2
{
    Type x;
    Type y;


    Vector2()
        :x(0)
        ,y(0)
    {
        //
    }

    Vector2(Type xVal, Type yVal)
    {
        x = xVal;
        y = yVal;
    }

    static Type DotProduct(const Vector2& lhs, const Vector2& rhs)
    {
        return (lhs.x * rhs.x) + (lhs.y * rhs.y);
    }

    static float Distance(const Vector2& lhs, const Vector2& rhs)
    {
        const float distanceX = lhs.x - rhs.x;
        const float distanceY = lhs.y - rhs.y;

        return std::sqrt(distanceX * distanceX + distanceY * distanceY);
    }

    Vector2 operator+(const Vector2& rhs)
    {
        return {x + rhs.x, y + rhs.y};
    }

    Vector2 operator-(const Vector2& rhs)
    {
        return {x - rhs.x, y - rhs.y};
    }

    Vector2& operator+=(const Vector2& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vector2& operator*=(const Vector2& rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }

    Vector2& operator*=(Type value)
    {
        x *= value;
        y *= value;
        return *this;
    }

    Vector2& operator/=(const Type& rhs)
    {
        return *this *= (1 / rhs);;
    }

    Vector2& operator=(const Vector2& rhs) = default;

    bool operator==(const Vector2& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vector2& other) const
    {
        return x != other.x && y != other.y;
    }

    Vector2& operator-()
    {
        return Vector2{ -x, -y };
    }

    /**
     * \brief Get Length of Vector2
     * \return Length of Vector2
     */
    Type Length()
    {
        return std::sqrt(LengthSquared());
    }

private:
    Type LengthSquared() const
    {
        return (x * x) + (y * y);
    }


};

using MurphLocation = Vector2<float>;
using MurphSize = Vector2<float>;


template <Number Type>
struct Vector3
{
    Type x;
    Type y;
    Type z;

public:
    Vector3()
        :x(0)
        ,y(0)
        ,z(0)
    {
        //
    }

    Vector3(const Type& xVal, const Type& yVal, const Type& zVal)
        :x(xVal)
        ,y(yVal)
        ,z(zVal)
    {
        //
    }

    Vector3(const Vector3& rhs)
        :x(rhs.x)
        ,y(rhs.y)
        ,z(rhs.z)
    {
        //
    }

    Vector3(Vector3&& rhs) noexcept
        :x(std::move(rhs.x))
        ,y(std::move(rhs.y))
        ,z(std::move(rhs.z))
    {
        //
    }

    ////// Operator Overloads //////

    bool operator==(const Vector3& rhs)
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    Vector3& operator+=(const Vector3& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    Vector3& operator-=(const Vector3& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    Vector3& operator*=(const Vector3& rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        return *this;
    }

    Vector3& operator/=(const Vector3& rhs)
    {
        return *this *= (1 / rhs);
    }

    Vector3& operator=(const Vector3& rhs)
    {
        if (this != &rhs)
        {
            this.x = rhs.x;
            this.y = rhs.y;
            this.z = rhs.z;
        }

        return *this;
    }

    Vector3& operator=(Vector3&& rhs) noexcept
    {
        if (this != &rhs)
        {
            this.x = std::move(rhs.x);
            this.y = std::move(rhs.y);
            this.z = std::move(rhs.z);
        }
        return *this;
    }

    friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
    {
        return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
    }

    friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
    {
        return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
    }

    friend Vector3 operator*(const Vector3& lhs, const Vector3& rhs)
    {
        return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
    }

    friend Vector3 operator*(Type multiplier, const Vector3& rhs)
    {
        return {multiplier * rhs.x, multiplier * rhs.y, multiplier * rhs.z};
    }

    friend Vector3 operator*(const Vector3& lhs, Type multiplier)
    {
        return multiplier * lhs;
    }

    friend Vector3 operator/(const Vector3& lhs, Type divisor)
    {
        return (1/ divisor) * lhs;
    }

    ///// Utility Functions /////

    static Type DotProduct(const Vector3& lhs, const Vector3& rhs)
    {
        const auto& vec1 = lhs.Normalized();
        const auto& vec2 = rhs.Normalized();

        return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
    }

    /**
     * \brief Get Cross Product of two Vector3.
     * \param lhs left side vector
     * \param rhs right side vector
     * \return Vector Orthogonal to both lhs and rhs
     */
    static Vector3 CrossProduct(const Vector3& lhs, const Vector3& rhs)
    {
        return {lhs.y * rhs.z - lhs.z * rhs.y,
                lhs.z * rhs.x - lhs.x * rhs.z,
                lhs.x * rhs.y - lhs.y * rhs.x};
    }

    /**
     * \brief Get Length of Vector3
     * \return length of vector
     */
    float Length() const
    {
        return std::sqrt(LengthSquared());
    }

    /**
     * \brief Normalize a Vector3
     * \return normalized vector
     */
    float Normalize()
    {
        return *this /= Length();
    }

    /**
     * \brief Get a normalized copy of a Vector3 without normalizing the vector itself.
     * \param lhs Vector we want a copy of the normalized version of
     * \return normalized copy of lhs (does not modify lhs) 
     */
    float Normalized(const Vector3& lhs) const
    {
        // copy of this
        Vector3 normalized = lhs;

        // return a copy of this normalized
        return normalized.Normalize();
    }

    static Vector3 GenerateRandomNormalizedVector3()
    {
        return GenerateRandomVector3(0, 1.0f);
    }

    static Vector3 GenerateRandomVector3(const Type& min, const Type& max);

private:
    Type LengthSquared() const
    {
        return (x * x) + (y * y) + (z * z);
    }

};

template <Number Type>
Vector3<Type> Vector3<Type>::GenerateRandomVector3(const Type& min, const Type& max)
{
    Vector3 randomVector;
    MurphRandomGenerator randomGen;

    randomVector.x = randomGen.GenerateRandomValueInclusive(min, max);
    randomVector.y = randomGen.GenerateRandomValueInclusive(min, max);
    randomVector.z = randomGen.GenerateRandomValueInclusive(min, max);

    return randomVector;
}
