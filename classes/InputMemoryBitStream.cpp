//
// Created by Nicolò Vanzo on 28/02/25.
//
#include "../headers/InputMemoryBitStream.h"
#include "../headers/CustomMath.h"
#include <math.h>

/**
 * I have used 2.f because the range of accepted values is [-1;+1] hence the formula would be:
 * (1 - (-1)) = 2
 * But why 65535? This is because we have a precision of 0.1 and with a value range of [-2000,2000] I have this formula:
 * (4000 / 0.1) + 1 = 40001
 * log2(40001) = 15.3 = 16
 * 2^16 = 65536
 * @param outQuat
 */
void InputMemoryBitStream::Read(Quaternion &outQuat) {
    float precision = (2.f / 65535.f);

    uint32_t f = 0;

    Read(f, 16);
    outQuat.mX = ConvertFromFixed(f, -1.f, precision);
    Read(f, 16);
    outQuat.mY = ConvertFromFixed(f, -1.f, precision);
    Read(f, 16);
    outQuat.mZ = ConvertFromFixed(f, -1.f, precision);

    outQuat.mW =  sqrtf(
            1.f -
            outQuat.mX * outQuat.mX +
            outQuat.mY * outQuat.mY +
            outQuat.mZ * outQuat.mZ
            );

    bool isNegative;
    Read(isNegative);

    if(isNegative) {
        outQuat.mW *= -1;
    }
}


