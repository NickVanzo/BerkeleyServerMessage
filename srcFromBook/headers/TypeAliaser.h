//
// Created by Nicolò Vanzo on 13/02/25.
//

#pragma once

// Generic type handling in C++
template <typename tFrom, typename tTo>
class TypeAliaser {
public:
    TypeAliaser(tFrom inFromValue) : mAsFromType(inFromValue) {}
    tTo& Get() {return mAsToType; }

    //Unions share the same memory location and the size is determined by the biggest of the two
    union {
        tFrom       mAsFromType;
        tTo         mAsToType;
    };
};