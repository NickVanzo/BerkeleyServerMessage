//
// Created by Nicolò Vanzo on 28/02/25.
//

#pragma once
#include <cstdlib>

inline uint32_t ConvertToFixed(float inNumber, float inMin, float inPrecision)
{
    return static_cast<uint32_t>((inNumber - inMin) / inPrecision);
}

inline float ConvertFromFixed(float inNumber, float inMin, float inPrecision)
{
    return static_cast<float>(inNumber) * inPrecision + inMin;
}
