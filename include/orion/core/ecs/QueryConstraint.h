//
// Created by Alex on 02/02/2024.
//

#ifndef ORION_QUERYCONSTRAINT_H
#define ORION_QUERYCONSTRAINT_H

#include "orion/core/type.h"
#include "orion/core/ecs/Filter.h"

#include <tuple>

namespace orion {

    template<typename T>
    class Marker {
    public:
        using value_type = T;
    };

    template<typename>
    struct is_marker : std::false_type {};

    template<typename T>
    struct is_marker<Marker<T>> : std::true_type {};

    template<typename>
    struct is_not_marker : std::true_type {};

    template<typename T>
    struct is_not_marker<Marker<T>> : std::false_type {};

    template<typename>
    struct is_not_marker_nested : std::true_type {};

    template<template<typename> typename Wrapper, typename T>
    struct is_not_marker_nested<Wrapper<Marker<T>>> : std::false_type {};

    template<typename T>
    concept RefType = std::is_reference_v<T> || is_marker<T>::value;

    template<typename T>
    struct TypeInfo {
        using value_type = std::decay_t<T>;
        bool  is_ref     = std::is_reference_v<T>;
        bool  is_const   = std::is_const_v<std::remove_reference_t<std::remove_pointer_t<T>>>;
        bool  is_marker   = ::orion::is_marker<T>::value;
    };

    template<typename... T>
    class Selector {
        static_assert(are_types_unique<T...>::value);
    public:
        using value_type          = std::tuple<T...>;
        using filtered_value_type = typename Filter<is_not_marker, std::tuple, T...>::type;
        using types_info          = std::tuple<TypeInfo<T>...>;
        using filtered_types_info = typename Filter<is_not_marker_nested, std::tuple, TypeInfo<T>...>::type;

        Selector();

        [[nodiscard]] static constexpr u32 size();

        template<size_t I = 0>
        void foreach(auto&& fun);

    protected:
        types_info m_types;
    };

    template<typename... T>
    constexpr u32 Selector<T...>::size() {
        return sizeof...(T);
    }

    template<typename... T>
    template<size_t I>
    void Selector<T...>::foreach(auto &&fun) {
        if constexpr (I < sizeof...(T)) {
            fun(std::get<I>(m_types), I);
            foreach<I + 1>(fun);
        }
    }

    template<typename... T>
    Selector<T...>::Selector() : m_types(types_info(TypeInfo<T>()...)) {}

    template<RefType... T>
    class Include : public Selector<T...> {
    public:
        using Selector<T...>::Selector;
    };

    template<typename>
    struct is_include : std::false_type {};

    template<typename... T>
    struct is_include<Include<T...>> : std::true_type {};

    template<typename... T>
    class Exclude : public Selector<T...> {
        static_assert((!is_marker<T>::value && ...));
    public:
        using Selector<T...>::Selector;
    };

    template<typename>
    struct is_exclude : std::false_type {};

    template<typename... T>
    struct is_exclude<Exclude<T...>> : std::true_type {};

    template<typename T>
    concept IncludeType = is_include<T>::value;

    template<typename T>
    concept ExcludeType = is_exclude<T>::value;

}

#endif //ORION_QUERYCONSTRAINT_H
