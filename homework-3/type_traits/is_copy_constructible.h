# pragma once

#include <type_traits>

#include "utility.h"

template<typename To, typename From>
struct is_invalid_lvalue_rvalue_cast
{
    constexpr static bool value = false;
};

template<typename T>
struct is_invalid_lvalue_rvalue_cast<T&&, T&>
{
    constexpr static bool value = true;
};

template<typename T>
struct is_invalid_lvalue_rvalue_cast<T&, T>
{
    constexpr static bool value = true;
};

template<typename T>
struct is_invalid_lvalue_rvalue_cast<T&, T&&>
{
    constexpr static bool value = true;
};

template <typename, typename T, typename... Args>
struct is_constructible_impl
{
    constexpr static bool value = false;
};

template <typename T, typename... Args>
struct is_constructible_impl<void_t<decltype(T(declval<Args>()...))>, T, Args...>
{
    constexpr static bool value = true;
};

template<typename T, typename... Args>
struct is_constructible
{
    constexpr static bool value = is_constructible_impl<void_t<>, T, Args...>::value && 
                                  !is_invalid_lvalue_rvalue_cast<T, Args...>::value;
};

template<typename T>
struct is_copy_constructible
{
    constexpr static bool value = is_constructible<T, T>::value;
};
