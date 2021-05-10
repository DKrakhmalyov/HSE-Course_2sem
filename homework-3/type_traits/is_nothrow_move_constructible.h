#pragma once 

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"

template<typename T, typename... Args>
struct is_nothrow_constructible {
    static constexpr bool value = noexcept(T(declval<Args>()...));
};

template<typename T, std::size_t N>
struct is_nothrow_constructible<T[N]> {
    static constexpr bool value = is_nothrow_constructible<T>::value;
};

template<typename T>
struct is_nothrow_move_constructible {
    static constexpr bool value = is_nothrow_constructible<T, T&&>::value;
};