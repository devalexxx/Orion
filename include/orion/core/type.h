//
// Created by Alex on 23/12/2023.
//

#ifndef ORION_TYPE_H
#define ORION_TYPE_H

#include <filesystem>
#include <vector>
#include <string>
#include <optional>

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

    using Index = u16;
    using IndexContainer = std::vector<Index>;

    template<typename T1, typename T2>
    using Pair = std::pair<T1, T2>;

    template<typename T>
    using EnumValue = typename std::underlying_type<T>::type;

    template<typename T>
    using OptRef = std::optional<std::reference_wrapper<const T>>;

    template<typename T>
    using OptRefMut = std::optional<std::reference_wrapper<T>>;

    using DynBitset = std::vector<bool>;

}

#endif //ORION_TYPE_H
