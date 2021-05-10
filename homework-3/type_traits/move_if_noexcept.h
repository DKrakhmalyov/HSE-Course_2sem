# pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"

// conditional
template<bool condition, typename T, typename F>
struct conditional;

template<typename T, typename F>
struct conditional<true, T, F> {
    using type = T;
};

template<typename T, typename F>
struct conditional<false, T, F> {
    using type = F;
};

template<bool condition, typename T, typename F>
using conditional_t = typename conditional<condition, T, F>::type;

template<typename T>
decltype(auto) move_if_noexcept(T&& value) {
    using F = uncvref_t<T>;
    return static_cast<conditional_t<is_nothrow_move_constructible<F>::value, F&&, F&>>(value);
}