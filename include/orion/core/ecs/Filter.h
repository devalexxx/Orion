//
// Created by Alex on 03/02/2024.
//

#ifndef ORION_FILTER_H
#define ORION_FILTER_H

#include <type_traits>

namespace orion {

    template<template<typename> typename , template<typename...> typename, typename...>
    struct Filter;

    template<template<typename> typename Pred, template<typename...> typename Variadic>
    struct Filter<Pred, Variadic>
    {
        using type = Variadic<>;
    };

    template<template<typename> typename Pred, template<typename...> typename Variadic, typename T, typename... Ts>
    struct Filter<Pred, Variadic, T, Ts...>
    {
        template<typename, typename>
        struct Cons;
        template<typename Head, typename... Tail>
        struct Cons<Head, Variadic<Tail...>>
        {
            using type = Variadic<Head, Tail...>;
        };

        using type = typename std::conditional<
                Pred<T>::value,
                typename Cons<T, typename Filter<Pred, Variadic, Ts...>::type>::type,
                typename Filter<Pred, Variadic, Ts...>::type>::type;
    };

    template <typename...>
    struct are_types_unique : std::true_type {};

    template <typename T, typename... Rest>
    struct are_types_unique<T, Rest...> : std::integral_constant<bool, (!std::is_same_v<std::decay_t<T>, std::decay_t<Rest>> && ...) && are_types_unique<Rest...>()> {};

}

#endif //ORION_FILTER_H
