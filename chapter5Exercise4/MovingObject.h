//
// Created by Nicolò Vanzo on 25/03/25.
//

#pragma once
#include "../srcFromBook/headers/GameObject.h"
#include "../srcFromBook/headers/ReflectionSystem.h"

#define OffsetOf(c, mv) ((size_t) & (static_cast<c*>(nullptr)->mv))

enum MovingObjectProperties
{
    MVP_MX  = 1 << 0,
    MVP_MY  = 1 << 1,
    MVP_MAX
};

class MovingObject : public GameObject {
    static DataType* sDataType;

    MovingObject();
    ~MovingObject();

    enum { kClassId = 'MVOB' };
    virtual uint32_t GetClassId() const {return kClassId;}
    static GameObject* CreateInstance() {return new MovingObject();}

    void Update();
    void Destroy();
    void Read(InputMemoryBitStream& outStream);
    void Write(OutputMemoryBitStream& inStream, uint32_t inProperties) const;
    static void InitDataType()
    {
    sDataType = new DataType(
            {
                MemberVariable("mX", EPT_Int, OffsetOf(MovingObject, mX)),
                MemberVariable("mY", EPT_Int, OffsetOf(MovingObject, mY))
            }
            );
    }
private:
    uint32_t mX;
    uint32_t mY;
};
