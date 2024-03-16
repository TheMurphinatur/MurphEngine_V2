#pragma once
#include <type_traits>
#include <random>
#include <chrono>
#include "MurphRandomGenerator.h"

template<class dataType>
concept Number = std::is_arithmetic_v<dataType>;

namespace MurphMath
{
    constexpr double kPi = 3.14159265358979323846f;

    // Will Interpolate between start and end by a normalized value (0.0f -> 1.0f)    
    template<Number Type>
    static constexpr Type Interpolate(Type start, Type end, const float normalizedVal)
    {
        assert(normalizedVal >= 0.0f && normalizedVal <= 1.0f);
        return (1 - normalizedVal) * start + normalizedVal * end;
    }

    template<Number Type>
    static constexpr Type ConvertDegreesToRadians(const float degrees)
    {
        return static_cast<Type>(degrees * (kPi / 180));
    }

    template<Number Type>
    static constexpr Type ConvertRadiansToDegrees(const float radians)
    {
        return static_cast<Type>(kPi * (radians / 180));
    }
    
}