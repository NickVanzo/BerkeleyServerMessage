//
// Created by Nicolò Vanzo on 03/03/25.
//

#pragma once
#include "cstdint"
#include "cstdlib"

class OutputMemoryBitStream {
public:
    OutputMemoryBitStream(bool isLittleEndian = true) : mBitHead(0), mBitCapacity(0), mIsLittleEndian(isLittleEndian)
        { ReallocBuffer(256);}
    ~OutputMemoryBitStream() { std::free(mBuffer); }

    void WriteBits(uint8_t inData, size_t inBitCount);
    void WriteBits(const void* inData, size_t inBitCount);
    void WriteBitsLittleEndian(uint8_t inData, size_t inBitCount);
    void WriteBitsBigEndian(uint8_t inData, size_t inBitCount);

    const char* GetBufferPtr()  const { return mBuffer; }
    uint32_t GetBitLength()     const { return mBitHead; }
    uint32_t GetByteLength()    const { return (mBitHead + 7) >> 3; }

    void WriteBytes(const void* inData, size_t inByteCount) {
        WriteBits(inData, inByteCount << 3);
    }
private:
    void ReallocBuffer(uint32_t inNewBitCapacity);
    char* mBuffer;
    uint32_t mBitHead;
    uint32_t mBitCapacity;
    bool mIsLittleEndian;
};


