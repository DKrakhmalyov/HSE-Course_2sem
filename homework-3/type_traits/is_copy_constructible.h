# pragma once

#include <type_traits>

#include "utility.h"

template<typename T, typename... Args>
struct is_constructible_impl : std::false_type {};

template<typename To, typename From>
struct is_invalid_lvalue_to_rvalue_cast : std::false_type {};

template<typename RefTo, typename RefFrom>
struct is_invalid_lvalue_to_rvalue_cast<RefTo&&, RefFrom&> : std::true_type {};

template<typename T, typename... Args>
struct is_constructible_impl<void_t<decltype(T(std::declval<Args>()...))>, T, Args...> : std::true_type {};

template<typename T, typename... Args>
struct is_constructible {
	constexpr static bool value = is_constructible_impl<void, T, Args...>::value && !is_invalid_lvalue_to_rvalue_cast<T, Args...>::value;
};

template<typename T>
struct is_copy_constructible {
	constexpr static bool value = is_constructible<T, add_lvalue_reference_t<add_const_t<T>>>::value;
};
