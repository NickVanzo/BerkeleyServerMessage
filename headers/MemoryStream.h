//
// Created by Nicolò Vanzo on 28/02/25.
//

#pragma once
#include <cstdlib>
#include <type_traits>
#include "ByteSwapper.h"
#include "config.h"
#include "./ReflectionSystem.h"

class MemoryStream {
    virtual void Serialize(void* ioData, uint32_t inByteCount) = 0;
    virtual bool IsInput() const = 0;

    template<typename T> void Serialize(T& ioData)
    {
        static_assert(
                std::is_arithmetic<T>::value || std::is_enum<T>::value,
                "Generic serialize only supports primitive data types"
                );

        #if STREAM_ENDIANNESS == PLATFORM_ENDIANNESS
            Serialize(ioData, inByteCount);
        #else
            if(IsInput())
            {
                T data;
                Serialize(&data, sizeof(data));
                ioData = ByteSwap(data);
            } else {
                T swappedData = ByteSwap(ioData);
                Serialize(&swappedData, sizeof(swappedData));
            }
        #endif
    }

    void Serialise(MemoryStream* inMemoryStream,
                   const DataType* inDataType, uint8_t* inData)
    {
        for(auto& mv : inDataType->GetMemberVariables())
        {
            void* mvData = inData + mv.GetOffset();
            switch (mv.GetPrimitiveType())
            {
                case EPT_Int:
                    inMemoryStream->Serialize(*(int*) mvData);
                    break;
                case EPT_String:
                    inMemoryStream->Serialize(*(std::string*) mvData);
                    break;
                case EPT_Float:
                    inMemoryStream->Serialize(*(float*) mvData);
                    break;
                default:
                    // Handle other enumeration values (e.g., log an error)
                    break;
            }
        }
    }
};
