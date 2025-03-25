//
// Created by Nicolò Vanzo on 16/02/25.
//
#include "../headers/OutputMemoryBitStream.h"
#include <algorithm>
#include "../headers/CustomMath.h"


void OutputMemoryBitStream::WriteBits(uint8_t inData, size_t inBitCount)
{
    uint32_t nextBitHead = mBitHead + static_cast<uint32_t>(inBitCount);
    if(nextBitHead > mBitCapacity)
    {
        ReallocBuffer(std::max(mBitCapacity * 2, nextBitHead));
    }
    //calculate the byteOffset into our buffer
    //by dividing the head by 8
    //and the bitOffset by taking the last 3 bits
    uint32_t byteOffset = mBitHead >> 3; // which byte I need to write into
    uint32_t bitOffset = mBitHead & 0x7; // the offset of the bit within that byte

    /**
     * currentMask creates a mask for the bits we DON'T want to change
     * if bitOffset is set to 3 the currentMask will be the following:
     *  ~(11111111 << 3) = ~(11111000) = 00000111
     */
    uint8_t currentMask = ~(0xff << bitOffset);
    mBuffer[byteOffset] = (mBuffer[byteOffset] & currentMask) | (inData << bitOffset);

    uint32_t bitsFreeThisByte = 8 - bitOffset;

    if(bitsFreeThisByte < inBitCount)
    {
        //we need another byte
        mBuffer[byteOffset + 1] = inData >> bitsFreeThisByte;
    }

    mBitHead = nextBitHead;
}

void OutputMemoryBitStream::WriteBits(const void *inData, size_t inBitCount)
{
    const char* srcByte = static_cast<const char*>(inData);
    while(inBitCount > 0)
    {
        WriteBits(*srcByte, 8);
        ++srcByte;
        inBitCount -= 8;
    }
    if(inBitCount > 0)
        WriteBits(*srcByte, inBitCount);
}

void OutputMemoryBitStream::ReallocBuffer(uint32_t inNewLength) {
    mBuffer = static_cast<char*>(std::realloc(mBuffer, inNewLength));
    mBitCapacity = inNewLength;
}
