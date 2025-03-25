//
// Created by Nicolò Vanzo on 13/02/25.
//

#pragma once
#include <cstdint>
#include "../headers/OutputMemoryBitStream.h"
#include "../headers/InputMemoryStream.h"
#include "../headers/InputMemoryBitStream.h"

class GameObject {
public:
    enum {kClassId = 'GOBJ'};
    virtual uint32_t GetClassId() const {return kClassId;}
    static GameObject* CreateInstance() {return new GameObject();}
    void Write(OutputMemoryBitStream& inStream) const {};
    void Read(InputMemoryStream& outStream) {};
    void Read(InputMemoryBitStream& outStream) {};
    void Destroy() {};
};
