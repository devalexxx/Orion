//
// Created by Alex on 05/02/2024.
//

#ifndef ORION_ASSERT_H
#define ORION_ASSERT_H

#include "fmt/core.h"
#include "fmt/color.h"

#ifdef _MSC_VER
#   define PRETTY_FUNCTION __FUNCSIG__
#else
#   define PRETTY_FUNCTION __PRETTY_FUNCTION__
#endif

#define ORION_ASSERT_IMPL(expr, format, ...)                                                    \
    (!(expr)) ?                                                                                 \
        (fmt::print(stderr, fg(fmt::color::red), "Assertion failed at {}:{} : {}\n",            \
        __FILE__, __LINE__, PRETTY_FUNCTION),                                                   \
        fmt::print(stderr, fg(fmt::color::orange), "\tassert  : \"{}\"\n\tmessage : ", #expr),  \
        fmt::print(stderr, fg(fmt::color::orange), format, ##__VA_ARGS__),                      \
        fmt::print(stderr, "\n"), abort(), 0) : 1

#ifdef ORION_DEBUG
#   define ORION_ASSERT(expr, format, ...) ORION_ASSERT_IMPL(expr, format, ##__VA_ARGS__)
#else
#   define ORION_ASSERT(expr, fmt, ...)
#endif

#endif //ORION_ASSERT_H
