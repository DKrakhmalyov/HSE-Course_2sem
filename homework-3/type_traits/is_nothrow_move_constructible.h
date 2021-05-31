#pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"


template<bool, bool, typename T, typename... Args>
struct is_nothrow_constructible_impl;

template<typename T, typename... Args>
struct is_nothrow_constructible {
    static constexpr bool value = noexcept(T(declval<Args>()...));
};

template<typename T>
struct is_nothrow_move_constructible {
    static constexpr bool value = is_nothrow_constructible<T,add_rvalue_reference_t<T>>::value;
};
