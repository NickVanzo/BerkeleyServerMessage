#include "OutputMemoryBitStream.h"
#include "algorithm"

void OutputMemoryBitStream::WriteBits(uint8_t inData, size_t inBitCount) {
    if(mIsLittleEndian)
        WriteBitsLittleEndian(inData, inBitCount);
    else
        WriteBitsBigEndian(inData, inBitCount);
}

void OutputMemoryBitStream::WriteBitsLittleEndian(uint8_t inData, size_t inBitCount) {
    uint32_t nextBitHead = mBitHead + static_cast<uint32_t>(inBitCount);

    if(nextBitHead > mBitCapacity)
        ReallocBuffer(std::max(mBitCapacity * 2, nextBitHead));

    uint32_t byteOffset = mBitHead >> 3;
    uint32_t bitOffset = mBitHead & 0x7;
    uint8_t currentMask = ~(0xff << bitOffset);

    mBuffer[byteOffset] = (mBuffer[byteOffset] & currentMask) | (inData << bitOffset);

    uint8_t bitsFreeThisByte = 8 - bitOffset;

    if(bitsFreeThisByte < inBitCount)
    {
        mBuffer[byteOffset + 1] = inData >> bitsFreeThisByte;
    }

    mBitHead = nextBitHead;
}

void OutputMemoryBitStream::WriteBitsBigEndian(uint8_t inData, size_t inBitCount)
{
    uint32_t nextBitHead = mBitHead + static_cast<uint8_t>(inBitCount);
    if(nextBitHead > mBitCapacity)
        ReallocBuffer(std::max(nextBitHead, mBitCapacity * 2));
    uint32_t byteOffset = mBitHead >> 3;
    uint32_t bitOffset = mBitHead & 0x7;
    uint32_t currentMask = ~(0xff >> (8 - bitOffset));
    mBuffer[byteOffset] = (mBuffer[byteOffset] & currentMask) | (inData >> (8 - bitOffset));
    uint8_t bitsFreeThisByte = 8 - bitOffset;

    if(bitsFreeThisByte < inBitCount)
    {
        mBuffer[byteOffset + 1] = inData << (8 - bitsFreeThisByte);
    }

    mBitHead = nextBitHead;
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

void OutputMemoryBitStream::ReallocBuffer(uint32_t inNewLength) {
    if(mBitCapacity == 0) {
        mBuffer = static_cast<char*>(std::malloc(inNewLength));
        mBitCapacity = inNewLength;
    } else {
        mBuffer = static_cast<char*>(std::realloc(mBuffer, inNewLength));
        mBitCapacity = inNewLength;
    }
}