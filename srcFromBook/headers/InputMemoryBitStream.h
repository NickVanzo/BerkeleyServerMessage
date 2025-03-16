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

    void Read(void* outData, uint32_t inBitCount) {
        if (mBitHead + inBitCount > mCapacity)
            inBitCount = mCapacity;

        /*
         * mBuffer points to the start of the buffer, mHead is the offset. So mBuffer + mHead actually is a pointer
         * to the data we have to read from the buffer
         */
        std::memcpy(outData, mBuffer + mBitHead, inBitCount);
        mBitHead += inBitCount;
    }

    template<typename T>
    void Read(T& outData, size_t inBitCount = sizeof(T) * 8)
    {
        static_assert(std::is_arithmetic<T>::Value || std::is_enum<T>::Value, "Incorrect type");
        if(mBitHead + inBitCount > mBitCounter)
            inBitCount = mBitCounter - mBiHead;
        std::memcpy(&outData, mBuffer + (mBitHead >> 3), (inBitCount + 7) >> 3);
        mBitHead += inBitCount;
    }

    void Read(uint32_t& outData) { Read(&outData, sizeof(outData)); }

    uint32_t GetRemainingBitCount() const {
        return mBitCounter - mBitHead;
    }
private:
    const char* mBuffer;
    uint32_t mBitCounter;
    uint32_t mBitHead;
    uint32_t mCapacity;
};
