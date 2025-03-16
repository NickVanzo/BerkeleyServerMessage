#pragma once
#include <cstring>  // For memcpy
#include <stdexcept>  // For exceptions
#include <unordered_map>
#include <iostream>

class InputMemoryStream {
public:
    InputMemoryStream(char* inBuffer, uint32_t inByteCount)
            : mBuffer(inBuffer), mCapacity(inByteCount), mHead(0) {
        std::cout << "Byte count: " << inByteCount << std::endl;
    }

    ~InputMemoryStream() { std::free(mBuffer); }

    uint32_t GetRemainingDataSize() const { return mCapacity - mHead; }

    void Read(void* outData, uint32_t inByteCount) {
        std::cout << "Reading " << inByteCount << " bytes from the buffer" << std::endl;

        if (mHead + inByteCount > mCapacity)
            inByteCount = mCapacity;

        /*
         * mBuffer points to the start of the buffer, mHead is the offset. So mBuffer + mHead actually is a pointer
         * to the data we have to read from the buffer
         */
        std::memcpy(outData, mBuffer + mHead, inByteCount);
        mHead += inByteCount;
        std::cout << "Bytes left in the buffer after reading: " << GetRemainingDataSize() << std::endl;
    }

    void Read(uint32_t& outData) { Read(&outData, sizeof(outData)); }
    void Read(int32_t& outData) { Read(&outData, sizeof(outData)); }
    void Read(std::unordered_map<int, int> &outData);

    template<typename tKey, typename tValue>
    void Read(std::unordered_map<tKey, tValue>& outData)
    {
        std::cout << "Read with template called" << std::endl;
        uint32_t size;
        Read(&size, sizeof(uint32_t));
        while(size > 0)
        {
            tKey first;
            tValue second;
            Read(&first, sizeof(tKey));
            Read(&second, sizeof(tValue));
            outData[first] = second;
            size -= 1;
        }
    }

private:
    char* mBuffer;
    uint32_t mHead;
    uint32_t mCapacity;
};
