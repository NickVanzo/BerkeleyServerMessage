/**
 *
 *  7. Explain thoroughly why the WriteBits function as implemented in this chapter only
    works properly on little-endian platforms. Implement a solution that will work on big-
    endian platforms as well.
 *
 */
#include "OutputMemoryBitStream.h"
#include "iostream"

int main(int argc, char* argv[])
{
    OutputMemoryBitStream mStream;
    uint32_t src = 12345;
    mStream.WriteBits(&src, sizeof(src) * 8);
    const char* bytes = mStream.GetBufferPtr();
    //https://stackoverflow.com/questions/12240299/convert-bytes-to-int-uint-in-c
    uint32_t res = bytes[0] + (bytes[1] << 8) + (bytes[2] << 16) + (bytes[3] << 32);
    uint32_t bigEndianRes = (bytes[0] << 32) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3];

    std::cout << "res: " << res << std::endl;
    std::cout << "res big endian: " << bigEndianRes << std::endl;
}