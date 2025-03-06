//
// Created by Nicolò Vanzo on 13/02/25.
//
#include "../headers/OutputMemoyStream.h"
#include "Quaternion.h"
#include <algorithm>

void OutputMemoryStream::ReallocBuffer(uint32_t inNewLength) {
    mBuffer = static_cast<char*>(std::realloc(mBuffer, inNewLength));
    //handle realloc errors
    mCapacity = inNewLength;
}

void OutputMemoryStream::Write(const void *inData, size_t inByteCount) {
    uint32_t resultHead = mHead + static_cast<uint32_t>(inByteCount);

    if(resultHead > mCapacity)
        ReallocBuffer(std::max(mCapacity * 2, resultHead));

    std::memcpy(mBuffer + mHead, inData, inByteCount);
    mHead = resultHead;
}

