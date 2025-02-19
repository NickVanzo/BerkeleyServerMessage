//
// Created by Nicolò Vanzo on 19/02/25.
//

#pragma once
#include <unordered_map>
#include "./GameObject.h"

class LinkingContext {
public:
    uint32_t GetNetworkId(GameObject* inGameObject)
    {
        auto it = mGameObjectToNetworkIdMap.find(inGameObject);
        if(it != mGameObjectToNetworkIdMap.end())
        {
            return it->second;
        }
        else
        {
            return 0;
        }
    }
    GameObject* GetGameObject(uint32_t inNetworkId)
    {
        auto it = mNetworkIdToGameObjectMap.find(inNetworkId);
        if(it != mNetworkIdToGameObjectMap.end())
        {
            return it->second;
        }
        else
        {
            return nullptr;
        }
    }
private:
    std::unordered_map<uint32_t, GameObject*> mNetworkIdToGameObjectMap;
    std::unordered_map<GameObject*, uint32_t> mGameObjectToNetworkIdMap;
};
