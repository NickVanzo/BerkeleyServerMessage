//
// Created by Nicolò Vanzo on 17/03/25.
//
#pragma once
#include "InputMemoryBitStream.h"
#include <unordered_map>
#include <assert.h>

// RPCUnwrapFunc is a pointer to a function that accepts a InputMemoryBitStream as param and returns void
typedef void (*RPCUnwrapFunc) (InputMemoryBitStream&);

class RPCManager
{
public:
    void RegisterUnwrapFunction(uint32_t inName, RPCUnwrapFunc inFunc)
    {
        assert(mNameToRPCTable.find(inName) != mNameToRPCTable.end());
        mNameToRPCTable[inName] = inFunc;
    }
    void ProcessRPC(InputMemoryBitStream& inStream)
    {
        uint32_t name;
        inStream.Read(name);
        mNameToRPCTable[name](inStream); //Call the function passing the inStream value as parameter
    }
    std::unordered_map<uint32_t, RPCUnwrapFunc> mNameToRPCTable;
};