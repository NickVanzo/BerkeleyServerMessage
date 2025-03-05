//
// Created by nvan on 04-03-2025.
//

#pragma once
#include <unordered_map>
#include "../headers/OutputMemoyStream.h"

class UnorderedMapConverted : public OutputMemoryStream {
public:
    void Write(const std::unordered_map<int, int>&);
};

