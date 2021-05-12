# pragma once

#include <type_traits>

#include "utility.h"

template<typename U, typename T, typename... Args>
struct is_constructible_impl : std::false_type {};

template<typename T, typename... Args>
struct is_constructible_impl 
    <std::void_t<decltype(T(std::declval<Args>()...))>, T, Args...> : std::true_type {};

template<typename T, typename... Args>
struct is_constructible : is_constructible_impl<void, T, Args...> {};

template<typename T>
struct is_constructible<T&&, T&> : std::false_type {};

template<typename T, typename... Args>
constexpr bool is_constructible_v = is_constructible<T, Args...>::value;

template<typename T>
struct is_copy_constructible 
    : is_constructible<T, add_lvalue_reference_t<add_const_t<T>>> {};

template<typename T>
constexpr bool is_copy_constructible_v = is_copy_constructible<T>::value;