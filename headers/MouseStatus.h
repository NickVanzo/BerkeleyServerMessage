//
// Created by Nicolò Vanzo on 02/03/25.
//

#pragma once
#include "string"
#include "./ReflectionSystem.h"
#define OffsetOf(c, mv) ((size_t) & (static_cast<c*>(nullptr)->mv))

class MouseStatus
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

};
