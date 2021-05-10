#pragma once 

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"

template<typename T, typename... Args>
struct is_nothrow_constructible
{
    constexpr static bool value = noexcept(T(declval<Args>()...));
};

template<typename T, std::size_t N>
struct is_nothrow_constructible<T[N]> 
{
    constexpr static bool value = is_nothrow_constructible<T>::value;
};

template<typename T>
struct is_nothrow_move_constructible 
{
    constexpr static bool value = is_nothrow_constructible<T, T&&>::value;
};