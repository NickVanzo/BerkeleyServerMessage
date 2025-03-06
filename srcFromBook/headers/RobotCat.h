//
// Created by Nicolò Vanzo on 13/02/25.
//

#pragma once
#include <cstdint>
#include "./GameObject.h"
#include "./OutputMemoyStream.h"
#include "./InputMemoryStream.h"
#include <vector>

class RoboCat {
public:
    RoboCat(): mHealth(10), mMeowCount(3), mHomeBase(0) {
        mName[0] = '\0';
    }
    virtual void Update();
    void Write(OutputMemoryStream& inStream) const;
    void Read(InputMemoryStream& inStream);
private:
    int32_t mHealth;
    int32_t mMeowCount;
    GameObject* mHomeBase;
    char mName[128];
    std::vector<int32_t> mMiceIndices;
};
