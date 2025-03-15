//
// Created by nvan on 12-03-2025.
//

#pragma once
#include "./GameObject.h"
#include <cstdint>
class RoboMouse : public GameObject
{
public:
    enum { kClassId = 'RBMS' };
    virtual uint32_t GetClassId() const {return kClassId;}
    static GameObject* CreateInstance() {return new RoboMouse();}
};