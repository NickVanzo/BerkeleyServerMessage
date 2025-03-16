
/**
 *
 *  Implement UnorderedMapConverted :: Write(const unordered_map<int, int >&)
    that allows the writing of a map from integer to integer into the stream.
 */

#include "./OutputMemoryBitStream.h"
#include "./InputMemoryStream.h"
#include <unordered_map>
#include <iostream>

int main(int argc, char* argv[])
{
    std::unordered_map<int, int> myMap;
    myMap[1] = 10;
    myMap[10] = 2;
    OutputMemoryBitStream myStream;
    myStream.Write(myMap);

    const char* buffer = myStream.GetBufferPtr();
    uint32_t bufferSize = myStream.GetByteLength();

    InputMemoryStream inputStream(const_cast<char*>(buffer), bufferSize);

    std::unordered_map<int, int> receivedMap;
    inputStream.Read(receivedMap);

    for(const auto& pair : receivedMap)
        std::cout << pair.first << " " << pair.second << std::endl;

    std::cout << "Byte in stream: " << myStream.GetByteLength() << std::endl;
    std::cout << "Bits in stream: " << myStream.GetBitLength() << std::endl;

    OutputMemoryBitStream mySecondStream;
    std::unordered_map<float, float> myFloatMap;

    myFloatMap[0.90] = 9.32;
    myFloatMap[0.112] = 2.331231;
    mySecondStream.Write(myFloatMap);
    const char* floatBuffer = mySecondStream.GetBufferPtr();
    uint32_t floatBufferBytes = mySecondStream.GetByteLength();

    InputMemoryStream mySecondInputStream(const_cast<char*>(floatBuffer), floatBufferBytes);
    std::unordered_map<float, float> receivedFloatMap;
    mySecondInputStream.Read(receivedFloatMap);

    for(const auto& pair : receivedFloatMap)
        std::cout << pair.first << " " << pair.second << std::endl;

    return 0;
}