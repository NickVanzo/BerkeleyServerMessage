//
// Created by Nicolò Vanzo on 06/03/25.
//
//
// Created by nvan on 04-03-2025.
//

#include "OutputMemoryBitStream.h"
#include "algorithm"

void OutputMemoryBitStream::Write(const std::unordered_map<int, int> & inMap)
{
    auto size = static_cast<uint32_t>(inMap.size());
    Write(size, sizeof(size));//4
    for(const auto& pair : inMap)
    {
        Write(pair.first, sizeof(pair.first)); //4
        Write(pair.second, sizeof(pair.second)); //4
    }
}

void OutputMemoryBitStream::WriteBits(uint8_t inData, size_t inBitCount)
{
    uint32_t newHead = static_cast<uint32_t>(inBitCount) + mBitHead;

    if(newHead > mBitCapacity)
    {
        ReallocBuffer(std::max(mBitCapacity * 2, newHead));
    }

    uint32_t byteOffset = mBitHead >> 3;
    uint32_t bitOffset = mBitHead & 0x7;
    uint8_t currentMask = ~(0xff << bitOffset);

    mBuffer[byteOffset] = (mBuffer[byteOffset] & currentMask) | (inData << bitOffset);

    uint8_t bitsFreeThisByte = 8 - bitOffset;

    if(bitsFreeThisByte < inBitCount)
    {
        mBuffer[byteOffset + 1] = inData >> bitsFreeThisByte;
    }

    mBitHead = newHead;
}

void OutputMemoryBitStream::WriteBits(const void *inData, size_t inBitCount)
{
    const char* srcByte = static_cast<const char*>(inData);

    while(inBitCount > 8)
    {
        WriteBits(*srcByte, 8);
        ++srcByte;
        inBitCount -= 8;
    }

    if(inBitCount > 0)
    {
        WriteBits(*srcByte, inBitCount);
    }
}

void OutputMemoryBitStream::ReallocBuffer(uint32_t inNewBitCapacity)
{
    mBuffer = static_cast<char*>(std::realloc(mBuffer, inNewBitCapacity));
    mBitCapacity = inNewBitCapacity;
}