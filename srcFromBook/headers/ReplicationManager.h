//
// Created by nvan on 15-03-2025.
//

#pragma once
#include "LinkingContext.h"
#include "OutputMemoryBitStream.h"
#include "InputMemoryBitStream.h"
#include "GameObject.h"
#include "vector"
#include "unordered_set"

class ReplicationManager
{
public:
    /*
     * Write replication data for a collection of object into an outgoing stream.
     * Tag the data as replication data and then call the RecplicateIntoStream function for each
     * GameObject in the vector.
     * For each object do the following steps:
     * 1. Write the network ID
     * 2. Write the object's class ID
     * 3. Use the Write function of the object to include its data into the outgoing stream
     * */
    void ReplicateWorldState(OutputMemoryBitStream& inStream, const std::vector<GameObject*>& inAllObjects);
    void ReceiveReplicateObjects(InputMemoryBitStream& inStream);
    void ReplicateCreate(OutputMemoryBitStream& inStream, GameObject* inGameObject);
    void ReplicateUpdate(OutputMemoryBitStream& inStream, GameObject* inGameObject);
    void ReplicateDestroy(OutputMemoryBitStream& inStream, GameObject* inGameObject);
    void ProcessReplicationAction(InputMemoryBitStream& inStream);
private:
    void ReplicationIntoStream(OutputMemoryBitStream& inStream, GameObject* inGameObject);
    GameObject* ReceiveReplicatedObject(InputMemoryBitStream& inStream);
    LinkingContext* mLinkingContext;
    std::unordered_set<GameObject*> mObjectsReplicatedToMe;
};