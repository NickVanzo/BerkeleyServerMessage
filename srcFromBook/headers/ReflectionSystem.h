//
// Created by Nicolò Vanzo on 01/03/25.
//

#pragma once
#include <cstdlib>
#include <string>
#include <vector>
#include <initializer_list>

enum EPrimitiveType {
    EPT_Int,
    EPT_String,
    EPT_Float
};

class MemberVariable {
public:
    MemberVariable(const char* inName,
            EPrimitiveType inPrimitiveType,
            uint32_t inOffset
            ) : mName(inName), mPrimitiveType(inPrimitiveType), mOffset(inOffset)
    {}

    EPrimitiveType GetPrimitiveType() const {return mPrimitiveType;}
    uint32_t GetOffset() const {return mOffset;}
private:
    std::string mName; // for debugging purpose
    EPrimitiveType mPrimitiveType;
    uint32_t mOffset;
};

class DataType {
public:
    DataType(std::vector<MemberVariable> inMVs) :
    mMemberVariables(inMVs)
    {}

    const std::vector<MemberVariable>& GetMemberVariables() const
    {
        return mMemberVariables;
    }
private:
    std::vector<MemberVariable> mMemberVariables;
};
