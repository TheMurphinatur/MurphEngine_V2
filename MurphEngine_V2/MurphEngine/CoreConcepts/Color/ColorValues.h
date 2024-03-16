#pragma once
#include <cstdint>


struct ColorValues
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;

    ColorValues(uint8_t redValue, uint8_t greenValue, uint8_t blueValue, uint8_t alphaValue)
    {
        red = redValue;
        blue = blueValue;
        green = greenValue;
        alpha = alphaValue;
    }
};
