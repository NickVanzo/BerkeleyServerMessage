//
// Created by Nicolò Vanzo on 13/02/25.
//

#pragma once
#include <cstdint>
#include <cstdlib>
#include <vector>
#include "Quaternion.h"
#include "MemoryStream.h

/**
 * Read FROM the data stream, this is a wrapper around a buffer allocated on the heap
 */
class InputMemoryStream : public MemoryStream
{
public:
    InputMemoryStream(char* inBuffer, uint32_t inByteCount)
        : mBuffer(mBuffer),
        mCapacity(inByteCount),
        mHead(0)
        {}
    ~InputMemoryStream() { free(mBuffer); }

    uint32_t GetRemainingDataSize() const { return mCapacity - mHead; }

    void Read(void* outData, uint32_t inByteCount);
    void Read(uint32_t& outData) { Read(&outData, sizeof(outData)); }
    void Read(int32_t outData) { Read(&outData, sizeof(outData)); }

    template<typename T>
    void Read(std::vector<T>& outVector) {
        size_t elementCount;
        Read(elementCount);
        outVector.resize(elementCount);
        for(const T& e : outVector) {
            Read(e);
        }
    }

    virtual void Serialize(void* ioData, uint32_t inByteCount)
    {
        Read(ioData, inByteCount);
    }
    virtual bool IsInput() const {return true;};
private:
    char* mBuffer;
    uint32_t mHead;
    uint32_t mCapacity;
};

