//
// Created by nvan on 16-03-2025.
//
#include "../headers/ReplicationHeader.h"
#include "../headers/RequireBitsUtilities.h"

void ReplicationHeader::Write(OutputMemoryBitStream &inStream)
{
    inStream.Write(mReplicationAction, GetRequiredBits<RA_MAX>::Value);
    inStream.Write(mNetworkId);
    if(mReplicationAction != RA_Destroy)
    {
        inStream.Write(mClassId);
    }
}

void ReplicationHeader::Read(InputMemoryBitStream &inStream)
{
    inStream.Read(mReplicationAction, GetRequiredBits<RA_MAX>::Value);
    inStream.Read(mNetworkId);
    if(mReplicationAction != RA_Destroy)
        inStream.Read(mClassId);
}