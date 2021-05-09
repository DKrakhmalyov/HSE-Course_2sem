# pragma once

#include <type_traits>

#include "utility.h"

/*
template<typename Derived, typename Base>
struct is_invalid_base_to_derived_cast {
    ...
};

template<typename To, typename From>
struct is_invalid_lvalue_to_rvalue_cast : std::false_type {
    ...
};

template<typename RefTo, typename RefFrom>
struct is_invalid_lvalue_to_rvalue_cast<RefTo&&, RefFrom&> {
    ...
};

struct is_constructible_helper {
    ...
};
*/

template<typename, typename T, typename... Args>
struct is_constructible_impl : std::false_type {};

template<typename T, typename... Args>
struct is_constructible_impl<void_t<decltype(T(declval<Args>()...))>, T, Args...> : std::true_type {};

template <typename T, class... Args>
struct is_constructible : is_constructible_impl<void_t<>, T, Args...> {};

template <typename T>
struct is_constructible<T&&, T&> : std::false_type {};

template<typename T>
struct is_copy_constructible : is_constructible<T, add_const_t<add_lvalue_reference_t<T>>> {};