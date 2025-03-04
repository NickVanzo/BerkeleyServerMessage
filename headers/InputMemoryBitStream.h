//
// Created by Nicolò Vanzo on 28/02/25.
//

#pragma once
#include "Quaternion.h"
#include <cstdlib>
class InputMemoryBitStream {
public:
    InputMemoryBitStream(const char* inBuffer, uint32_t inBitCount):
        mBuffer(inBuffer), mBitCounter(inBitCount), mBitHead(0) {}

    void Read(uint32_t& outData, uint32_t inBitCount);
    void Read(bool& outData);
    void Read(Quaternion& outQuat);
private:
    const char* mBuffer;
    uint32_t mBitCounter;
    uint32_t mBitHead;
};
