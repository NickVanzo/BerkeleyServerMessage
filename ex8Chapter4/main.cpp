
/**
 *
 *  Implement UnorderedMapConverted :: Write(const unordered_map<int, int >&)
    that allows the writing of a map from integer to integer into the stream.
 */

#include "./UnorderedMapConverted.h"

int main(int argc, char* argv[])
{
    std::unordered_map<int, int> myMap = {
            {1, 1},
            {4, 10}
    };
    UnorderedMapConverted myStream;
    myStream.Write(myMap);
}