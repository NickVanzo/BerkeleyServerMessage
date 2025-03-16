//
// Created by nvan on 15-03-2025.
//

template<int tValue, int tBits>
struct GetRequiredBitsHelper
{
    enum {Value = GetRequiredBitsHelper<(tValue >> 1), tBits + 1>::Value};
};

template<int tBits>
struct GetRequiredBitsHelper<0, tBits>
{
    enum {Value = tBits};
};

template<int tValue>
struct GetRequiredBits
{
    enum {Value = GetRequiredBitsHelper<tValue, 0>::Value};
};