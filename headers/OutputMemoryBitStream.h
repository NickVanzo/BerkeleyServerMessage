//
// Created by Nicolò Vanzo on 16/02/25.
//

#pragma once
#include <cstdlib>
#include <type_traits>
#include <vector>
/**
 * We often want to be able to send as few bits as possible to the server
 */
class OutputMemoryBitStream {
public:
    OutputMemoryBitStream() { ReallocBuffer(256); }
    ~OutputMemoryBitStream() { free(mBuffer); }

    /**
     * Write bits to the stream
     * @param inData single byte
     * @param inBitCount given unmber of bits to write from that byte into the stream
     */
    void WriteBits(uint8_t inData, size_t inBitCount);
    void WriteBits(const void* inData, size_t inBitCount);

    void WriteBytes(const void* inData, size_t inByteCount) {
        WriteBits(inData, inByteCount << 3);
    }
    void WriteBytes(uint32_t inData, size_t inBitCount = sizeof(uint32_t) * 8) {
        WriteBits(&inData, inBitCount);
    }
    void WriteBytes(float inData) {
        WriteBits(&inData, sizeof(float) * 8);
    }
    void WriteBytes(uint16_t inData, size_t bitCount = sizeof(uint16_t) * 8) {
        WriteBits(&inData, bitCount);
    }
    void WriteBytes(int16_t inData, size_t bitCount = sizeof(int16_t) * 8) {
        WriteBits(&inData, bitCount);
    }
    void WriteBytes(uint8_t inData, size_t bitCount = sizeof(uint8_t) * 8) {
        WriteBits(&inData, bitCount);
    }
    void WriteBytes(bool inData) {
        WriteBits(&inData, 1);
    }

    /**
     * This works only on little-endian machines, the big-endian implementation is left as an exercise
     * @tparam T
     * @param inData
     * @param inBitCount
     */
    template<typename T>
    void Write(T inData, size_t inBitCount = sizeof(T) * 8) {
        static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value, "Generic write only supports primitve types");
        WriteBits(&inData, inBitCount);
    }

    template<typename T>
    void Write(const std::vector<T>& inVector) {
        size_t elementCount = inVector.size();
        Write(elementCount);
        for(const T& element : inVector) {
            Write(element);
        }
    }



    const char* GetBufferPtr() const {return mBuffer;}
    uint32_t    GetBitLength() const {return mBitHead;}
    /**
     * The >> 3 shift means "divide the left value by the power of 2 ^ 3"
     * If we had >> 4 it would have been 2 ^ 4
     * The "+7" is to avoid rounding errors.
     * @return
     */
    uint32_t    GetByteLength() const {return (mBitHead + 7) >> 3;}
private:
    void ReallocBuffer(uint32_t inNewBitCapacity);
    char* mBuffer;
    uint32_t mBitHead;
    uint32_t mBitCapacity;
};