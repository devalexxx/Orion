//
// Created by Alex on 23/12/2023.
//

#ifndef ORION_TYPE_H
#define ORION_TYPE_H

#include <filesystem>
#include <string>

namespace orion {

    using i8 = char;
    using u8 = unsigned char;

    using i16 = short;
    using u16 = unsigned short;

    using i32 = int;
    using u32 = unsigned int;

    using i64 = long long int;
    using u64 = unsigned long long int;

    using f32 = float;
    using f64 = double;

    using String = std::string;

    template<typename T>
    using Ref = const T&;

    template<typename T>
    using RefMut = T&;

    template<typename T>
    using Ptr = const T*;

    template<typename T>
    using PtrMut = T*;

    namespace filesystem = std::filesystem;
    using Path = filesystem::path;

}

#endif //ORION_TYPE_H
