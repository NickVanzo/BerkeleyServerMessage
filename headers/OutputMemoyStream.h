//
// Created by Nicolò Vanzo on 13/02/25.
//
#pragma once
#include <cstdint>
#include <cstdlib>

/**
 * An output memory stream acts as a source of input for the user
 * From input to stream
 */
class OutputMemoryStream
{
public:
    OutputMemoryStream(): mBuffer(nullptr), mHead(0), mCapacity(0) {
        ReallocBuffer(32);
    }
    ~OutputMemoryStream() {free(mBuffer);};
    const char* GetBufferPtr() const { return mBuffer; }
    uint32_t GetLength() const { return mHead; }

    void Write(const void* inData, size_t inByteCount);
    void Write(uint32_t inData) { Write(&inData, sizeof(inData));}
    void Write(int32_t inData) { Write(&inData, sizeof(inData)); }

private:
    void ReallocBuffer(uint32_t inNewLength);
    char* mBuffer;
    uint32_t mHead;
    uint32_t mCapacity;
};