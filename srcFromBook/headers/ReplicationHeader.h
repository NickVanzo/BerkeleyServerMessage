//
// Created by nvan on 16-03-2025.
//

#pragma once
#include <cstdint>
#include "OutputMemoryBitStream.h"
#include "InputMemoryBitStream.h"

enum ReplicationAction
{
    RA_Create,
    RA_Update,
    RA_Destroy,
    RA_RPC,
    RA_MAX
};

class ReplicationHeader
{
public:
    ReplicationHeader() {}
    ReplicationHeader(ReplicationAction inRA, uint32_t inNetworkId, uint32_t inClassId = 0):
    mReplicationAction(inRA), mNetworkId(inNetworkId), mClassId(inClassId)
    {}

    ReplicationAction mReplicationAction;
    uint32_t          mNetworkId;
    uint32_t          mClassId;

    void Write(OutputMemoryBitStream& inStream);
    void Read(InputMemoryBitStream& inStream);
};