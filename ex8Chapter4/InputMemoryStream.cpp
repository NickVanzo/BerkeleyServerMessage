//
// Created by nvan on 06-03-2025.
//

#include "InputMemoryStream.h"

void InputMemoryStream::Read(std::unordered_map<int, int> &outData)
{
    uint32_t elementsInMap = 0;
    Read(&elementsInMap, sizeof(uint32_t));

    while(elementsInMap > 0)
    {
        uint32_t first;
        uint32_t second;
        Read(&first, sizeof(int));
        Read(&second, sizeof(int));
        outData[first] = second;
        --elementsInMap;
    }
}
