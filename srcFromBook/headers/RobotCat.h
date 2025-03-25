//
// Created by Nicolò Vanzo on 13/02/25.
//

#pragma once
#include <cstdint>
#include "./GameObject.h"
#include "./OutputMemoyStream.h"
#include "./InputMemoryStream.h"
#include <vector>

class RoboCat  : public GameObject {
public:
    RoboCat(): mHealth(10), mMeowCount(3), mHomeBase(0) {
        mName[0] = '\0';
    }
    enum {kClassId = 'RBTC'};
    virtual void Update();

    void Write(OutputMemoryBitStream& inStream) const;
    void Read(InputMemoryBitStream& inStream);


    virtual uint32_t GetClassId() const {return kClassId;}
    static GameObject* CreateInstance() {return new RoboCat();}
private:
    int32_t mHealth;
    int32_t mMeowCount;
    GameObject* mHomeBase;
    char mName[128];
    std::vector<int32_t> mMiceIndices;
};
