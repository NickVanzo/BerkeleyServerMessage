//
// Created by nvan on 16-03-2025.
//
#include "../headers/MouseStatus.h"
#include "../headers/RequireBitsUtilities.h"

void MouseStatus::Write(OutputMemoryBitStream &inStream, uint32_t inProperties)
{
    inStream.Write(inProperties, GetRequiredBits<MSP_MAX>::Value);
    if((inProperties & MSP_Name) != 0)
        inStream.Write(mName);

    if((inProperties & MSP_LegCount) != 0)
        inStream.Write(mLegCount);

    if((inProperties & MPS_HeadCount) != 0)
        inStream.Write(mHeadCount);

    if((inProperties & MSP_Health) != 0)
        inStream.Write(mHealth);
}

void MouseStatus::Read(InputMemoryBitStream &outStream)
{
    uint32_t writtenProperties;
    outStream.Read<uint32_t>(writtenProperties, GetRequiredBits<MSP_MAX>::Value);
    if((writtenProperties & MSP_Name) != 0)
        outStream.Read(mName);

    if((writtenProperties & MSP_LegCount) != 0)
        outStream.Read(mLegCount);

    if((writtenProperties & MPS_HeadCount) != 0)
        outStream.Read(mHeadCount);

    if((writtenProperties & MSP_Health) != 0)
        outStream.Read(mHealth);
}