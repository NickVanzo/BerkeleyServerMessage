//
// Created by Nicolò Vanzo on 19/02/25.
//

#pragma once
#include <unordered_map>
#include "./GameObject.h"

class LinkingContext {
public:
    LinkingContext(): mNextNetworkId(1) {}



    uint32_t GetNetworkId(GameObject* inGameObject, bool shouldCreateIfNotFound)
    {
        auto it = mGameObjectToNetworkIdMap.find(inGameObject);
        if(it != mGameObjectToNetworkIdMap.end())
        {
            return it->second;
        }
        else if(shouldCreateIfNotFound)
        {
            uint32_t newNetworkId = mNextNetworkId++;
            AddGameObject(inGameObject, newNetworkId);
            return newNetworkId;
        } else {
            return 0;
        }
    }

    void AddGameObject(GameObject* inGameObject, uint32_t networkId)
    {
        mNetworkIdToGameObjectMap[networkId] = inGameObject;
        mGameObjectToNetworkIdMap[inGameObject] = networkId;
    }

    void RemoveGameObject(GameObject* inGameObject)
    {
        uint32_t networkId = mGameObjectToNetworkIdMap[inGameObject];
        mGameObjectToNetworkIdMap.erase(inGameObject);
        mNetworkIdToGameObjectMap.erase(networkId);
    }

    GameObject* GetGameObject(uint32_t inNetworkId);
private:
    std::unordered_map<uint32_t, GameObject*> mNetworkIdToGameObjectMap;
    std::unordered_map<GameObject*, uint32_t> mGameObjectToNetworkIdMap;
    uint32_t mNextNetworkId;
};
