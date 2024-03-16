#include "MurphRandomGenerator.h"

#include <chrono>
#include <iostream>

MurphRandomGenerator::MurphRandomGenerator()
{
    const auto realTime = std::chrono::system_clock::now().time_since_epoch().count();
    const auto seed = static_cast<uint64_t>(realTime);
    UpdateSeed(seed);
}

MurphRandomGenerator::MurphRandomGenerator(uint64_t seed)
{
    UpdateSeed(seed);
}

void MurphRandomGenerator::UpdateSeed(uint64_t newSeed)
{
    m_seed = newSeed;
    SetNewState();
}

float MurphRandomGenerator::GenerateRandomNormalizedValue()
{
    return static_cast<float>(XorShiftGenerate(m_state)) / (static_cast<float>(UINT64_MAX) - 1);
}

bool MurphRandomGenerator::GenerateRandomBoolean()
{
    return GenerateRandomNormalizedValue() >= 0.5f;
}

void MurphRandomGenerator::SetNewState()
{
    m_state[0] = m_seed;
    m_state[1] = m_seed;
}

uint64_t MurphRandomGenerator::MangleBits(uint64_t value)
{
    value *= 0x6c50b47c6a77b2c8;
    value ^= value >> 32;
    return value;
}

uint64_t MurphRandomGenerator::XorShiftGenerate(uint64_t state[2])
{
    uint64_t t = state[0];
    uint64_t const s = state[1];

    state[0] = s;
    t ^= t << 23;
    t ^= t >> 18;
    t ^= s ^ (s >> 5);

    state[1] = t;

    return MangleBits(t + s);
}
