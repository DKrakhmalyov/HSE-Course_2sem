# pragma once

#include <type_traits>

#include "utility.h"

template<typename T, typename... Args>
struct is_constructible_impl : std::false_type {};

template<typename T, typename... Args>
struct is_constructible_impl<decltype(T(std::declval<Args>()...), void()), T, Args...> : std::true_type {};

template<typename T, typename... Args>
struct is_constructible : is_constructible_impl<void, T, Args...> {};

template<typename T>
struct is_constructible<T&&, T&> : std::false_type {};

template<typename T>
struct is_copy_constructible : is_constructible<T, add_lvalue_reference_t<add_const_t<T>>> {};
