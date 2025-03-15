//
// Created by nvan on 12-03-2025.
//

#pragma once
#include "GameObject.h"
#include "RobotCat.h"
#include "RoboMouse.h"
#include <cassert>
#include <unordered_map>

typedef GameObject* (*GameObjectCreationFunc)();

/*
 * Link an object id to a creation function. This class will be mainly used by the linker when the object
 * the host is receiving cannot be found.
 * */
class ObjectCreationRegistry
{
public:
    //Singleton pattern
    static ObjectCreationRegistry& Get()
    {
        static ObjectCreationRegistry sInstance;
        return sInstance;
    }

    template<class T> void RegisterCreationFunction()
    {
        //Check if the class id is already registered
        assert(
                mNameToGameObjectCreationFunctionMap.find(T::kClassId) ==
                mNameToGameObjectCreationFunctionMap.end()
        );
        mNameToGameObjectCreationFunctionMap[T::kClassId] = T::CreateInstance;
    }

    GameObject* CreateGameObject(uint32_t inClassId)
    {
        GameObjectCreationFunc creationFunc = mNameToGameObjectCreationFunctionMap[inClassId];
        GameObject* gameObject = creationFunc();
        return gameObject;
    }

private:
    ObjectCreationRegistry() {}
    std::unordered_map<uint32_t, GameObjectCreationFunc> mNameToGameObjectCreationFunctionMap;

    void RegisterObjectCreation()
    {
        ObjectCreationRegistry::Get().RegisterCreationFunction<GameObject>();
        ObjectCreationRegistry::Get().RegisterCreationFunction<RoboCat>();
        ObjectCreationRegistry::Get().RegisterCreationFunction<RoboMouse>();
    }
};