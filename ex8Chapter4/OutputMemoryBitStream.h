//
// Created by nvan on 04-03-2025.
//

#pragma once
#include <unordered_map>

class OutputMemoryBitStream {
public:
    OutputMemoryBitStream() :
    mBuffer(nullptr), mBitHead(0), mBitCapacity(0)
    { ReallocBuffer(256);}
    ~OutputMemoryBitStream() {std::free(mBuffer);}

    void WriteBits(const void* inData, size_t inBitCount);
    void WriteBits(uint8_t inData, size_t inBitCount);

    const char* GetBufferPtr() const {return mBuffer;}
    uint32_t GetBitLength() const {return mBitHead;}
    uint32_t GetByteLength() const {return (mBitHead + 7) >> 3;}

    void WriteBytes(const void* inData, size_t inByteCount)
    {
        WriteBits(inData, inByteCount << 3);
    }

    void Write(const std::unordered_map<int, int>&);
    void Write(uint32_t inData, size_t inBitCount = sizeof(uint32_t) * 8) { WriteBits(inData, inBitCount);}

private:
    void ReallocBuffer(uint32_t inNewBitCapacity);
    char* mBuffer;
    uint32_t mBitHead;
    uint32_t mBitCapacity;
};

