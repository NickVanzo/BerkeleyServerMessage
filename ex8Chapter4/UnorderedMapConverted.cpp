//
// Created by nvan on 04-03-2025.
//

#include "UnorderedMapConverted.h"

void UnorderedMapConverted::Write(const std::unordered_map<int, int> & inMap)
{
    uint32_t size = static_cast<uint32_t>(inMap.size());
    OutputMemoryStream::Write(&size, sizeof(size));
    for(const auto& pair : inMap)
    {
        OutputMemoryStream::Write(&pair.first, sizeof(int));
        OutputMemoryStream::Write(&pair.second, sizeof(int));
    }
}
