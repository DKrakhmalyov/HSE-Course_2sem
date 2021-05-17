#pragma once 
#include <type_traits>
#include "is_copy_constructible.h"
#include "utility.h"

template<bool is_constructible, typename T, typename... Args>
struct is_nothrow_constructible_impl : std::false_type {};

template<typename T, typename... Args>
struct is_nothrow_constructible_impl<1, T, Args...> :  std::integral_constant<bool, noexcept(T(std::declval<Args>()...))> {};


template<typename T, typename... Args>
struct is_nothrow_constructible : is_nothrow_constructible_impl<is_constructible<T, Args...>::value, T, Args...> {};

template<typename T, std::size_t N>
struct is_nothrow_constructible<T[N]> : std::false_type {};

template<typename T>
struct is_nothrow_move_constructible : is_nothrow_constructible<T, T&&> {};