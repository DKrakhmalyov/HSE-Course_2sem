#pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"

//<is_constructible, is_reference, T, Args...>
template<bool IC, bool IR, typename T, typename... Args>
struct is_nothrow_constructible_impl : std::conjunction<
        std::bool_constant<IC>,
        std::disjunction<
                std::bool_constant<IR>,
                std::bool_constant<noexcept(T(std::declval<Args>()...))>
        >
> {
};

// is_nothrow_constructible_impl - partial specializations


template<typename T, typename... Args>
struct is_nothrow_constructible : is_nothrow_constructible_impl<
        is_constructible<T, Args...>::value,
        false,
        T,
        Args...
> {
};

template<typename T, typename... Args>
struct is_nothrow_constructible<T &, Args...> : is_nothrow_constructible_impl<
        is_constructible<T, Args...>::value,
        true,
        T,
        Args...
> {
};

template<typename T, typename... Args>
struct is_nothrow_constructible<T &&, Args...> : is_nothrow_constructible_impl<
        is_constructible<T, Args...>::value,
        true,
        T,
        Args...
> {
};

template<typename T>
struct is_nothrow_move_constructible : is_nothrow_constructible<T, T &&> {
};