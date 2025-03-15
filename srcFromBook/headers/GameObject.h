//
// Created by Nicolò Vanzo on 13/02/25.
//

#pragma once
#include <cstdint>

class GameObject {
public:
    enum {kClassId = 'GOBJ'};
    virtual uint32_t GetClassId() const {return kClassId;}
    static GameObject* CreateInstance() {return new GameObject();}
};
