
/**
 *
 *  Implement UnorderedMapConverted :: Write(const unordered_map<int, int >&)
    that allows the writing of a map from integer to integer into the stream.
 */

#include "./OutputMemoryBitStream.h"
#include <unordered_map>
#include <iostream>

int main(int argc, char* argv[])
{
    std::unordered_map<int, int> myMap;
    myMap[1] = 10;
    myMap[10] = 2;
    OutputMemoryBitStream myStream;
    myStream.Write(myMap);
    std::cout << sizeof(uint32_t) << std::endl;
    std::cout << myStream.GetByteLength() << std::endl;
}