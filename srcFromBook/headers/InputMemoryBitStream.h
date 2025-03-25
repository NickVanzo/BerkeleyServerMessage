//
// Created by Nicolò Vanzo on 28/02/25.
//

#pragma once
#include "Quaternion.h"
#include <cstdlib>
#include <type_traits>
#include <cstring>
#include "string"

class InputMemoryBitStream {
public:
    InputMemoryBitStream(const char* inBuffer, uint32_t inBitCount):
        mBuffer(inBuffer), mBitCounter(inBitCount), mBitHead(0) {}

//    void Read(uint32_t& outData, uint32_t inBitCount);
    void Read(bool& outData);

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
        static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value, "Incorrect type");
        if(mBitHead + inBitCount > mBitCounter)
            inBitCount = mBitCounter - mBitHead;
        std::memcpy(&outData, mBuffer + (mBitHead >> 3), (inBitCount + 7) >> 3);
        mBitHead += inBitCount;
    }

    void Read(std::string& outData)
    {
        uint32_t l;
        Read(l, sizeof(uint32_t) * 8);
        outData.resize(l);
        for(int i = 0; i < l; ++i) {
            uint8_t c;
            Read(c, 8);
            outData[i] = static_cast<char>(c);
        }
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
