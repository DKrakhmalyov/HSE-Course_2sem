# pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"

// conditional
template<bool condition, typename T, typename F>
struct conditional {
    using type = T;
};

template<typename T, typename F>
struct conditional<false, T, F> {
    using type = F;
};

// conditional - partial specialization

template<bool condition, typename T, typename F>
using conditional_v = typename conditional<condition, T, F>::type;

// move_if_noexcept

template< class T >
constexpr typename conditional<
        std::conjunction_v<std::negation<is_nothrow_move_constructible<T>>,  is_copy_constructible<T>>,
        const T&,
        T&&
>::type move_if_noexcept(T& x) noexcept;
