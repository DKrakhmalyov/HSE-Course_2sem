#pragma once

#include <type_traits>
#include "utility.h"

template<typename T, typename... Args>
struct is_constructible_impl : std::false_type {
};

template<typename T, typename... Args>
struct is_constructible_impl<wrap_t<decltype(T(std::declval<Args>()...))>, T, Args...> : std::true_type {
};

template<typename T, typename... Args>
struct is_constructible : is_constructible_impl<empty_wrap_t, T, Args...> {
};

template<typename T>
struct is_constructible<T &&, T &> : std::false_type {
};

template<typename T>
struct is_copy_constructible : is_constructible<T, add_lvalue_reference<add_const_t<T>>> {
};