//
// Created by Nicolò Vanzo on 10/03/25.
//
#include "../headers/LinkingContext.h"

GameObject *LinkingContext::GetGameObject(uint32_t inNetworkId)
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