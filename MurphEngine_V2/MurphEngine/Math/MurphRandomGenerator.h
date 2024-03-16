#pragma once
#include <chrono>
#include <type_traits>

class MurphRandomGenerator
{
    uint64_t m_seed;
    uint64_t m_state[2];

public:
    MurphRandomGenerator();
    MurphRandomGenerator(uint64_t seed);

    void UpdateSeed(uint64_t newSeed);
    float GenerateRandomNormalizedValue();

    bool GenerateRandomBoolean();

    template <typename Type>
    requires std::is_arithmetic_v<Type>
    Type GenerateRandomValueInclusive(Type min, Type max)
    {
        if (min > max)
            std::swap(min, max);

        return static_cast<Type>(min + GenerateRandomNormalizedValue() * ((max + 1) - min));
    }

    template <typename Type>
        requires std::is_arithmetic_v<Type>
    Type GenerateRandomValueNonInclusive(Type min, Type max)
    {
        if (min > max)
            std::swap(min, max);

        return static_cast<Type>(min + GenerateRandomNormalizedValue() * (max - min));
    }

    template <typename Type>
    Type GenerateWeightedRandom(const std::vector<std::pair<Type, float>>& weightedItems)
    {
        // calculate total weight
        float totalWeight = 0.0f;
        for (const auto & item : weightedItems)
            totalWeight += item.second;

        float randomVal = GenerateRandomNormalizedValue() * totalWeight;
        for (const auto & item : weightedItems)
        {
            if (randomVal < item.second)
                return item.first;
            randomVal -= item.second;
        }
        return Type();
    }
private:
    void SetNewState();
    static uint64_t MangleBits(uint64_t value);
    static uint64_t XorShiftGenerate(uint64_t state[2]);
};
