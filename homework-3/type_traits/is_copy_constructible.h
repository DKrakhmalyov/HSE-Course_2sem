#pragma once

#include <type_traits>

#include "utility.h"

template <typename, typename T, typename... Args>
struct is_constructible_impl : std::false_type {};

template <typename T, typename... Args>
struct is_constructible_impl<
    decltype(T(myDeclval<Args>()...), std::true_type()), T, Args...>
    : std::true_type {};

template <typename T, typename... Args>
struct is_constructible : is_constructible_impl<std::true_type, T, Args...> {};

template <typename T>
struct is_constructible<T&, T> : std::false_type {};

template <typename T>
struct is_constructible<T&, T&&> : std::false_type {};

template <typename T>
struct is_constructible<T&&, T&> : std::false_type {};

template <typename T>
struct is_copy_constructible
    : is_constructible<std::true_type, T, add_lvalue_reference_t<T>> {};
