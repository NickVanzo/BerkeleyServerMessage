//
// Created by Nicolò Vanzo on 02/03/25.
//

#pragma once
#include "string"
#include "./GameObject.h"
#include "./ReflectionSystem.h"
#define OffsetOf(c, mv) ((size_t) & (static_cast<c*>(nullptr)->mv))

enum MouseStatusProperties
{
    MSP_Name        = 1 << 0,
    MSP_LegCount    = 1 << 1,
    MPS_HeadCount   = 1 << 2,
    MSP_Health      = 1 << 3,
    MSP_MAX
};

class MouseStatus : public GameObject
{
public:
    std::string     mName;
    int             mLegCount, mHeadCount;
    float           mHealth;

    static DataType* sDataType;
    static void InitDataType()
    {
        sDataType = new DataType(
                {
                    MemberVariable("mName", EPT_String, OffsetOf(MouseStatus, mName)),
                    MemberVariable("mLegCount", EPT_Int, OffsetOf(MouseStatus, mName)),
                    MemberVariable("mHeadCount", EPT_Int, OffsetOf(MouseStatus, mHeadCount)),
                    MemberVariable("mHealth", EPT_Float, OffsetOf(MouseStatus, mHeadCount))
                });
    };

    void Write(OutputMemoryBitStream& inStream, uint32_t inProperties);
    void Read(InputMemoryBitStream& outStream);

};
