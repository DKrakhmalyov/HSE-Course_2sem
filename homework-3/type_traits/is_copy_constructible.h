# pragma once

#include <type_traits>

#include "utility.h"

template<typename To, typename From>
struct is_invalid_lvalue_to_rvalue_cast : public std::false_type {  };

template<typename RefTo, typename RefFrom>
struct is_invalid_lvalue_to_rvalue_cast<RefTo&&, RefFrom&> : public std::true_type{  };

template<typename To, typename From>
using is_invalid_lvalue_to_rvalue_cast_v = typename is_invalid_lvalue_to_rvalue_cast<To, From>::value;


template<typename... Args>
using void_t = void;


template<typename U, typename T, typename... Args>
struct is_constructible_impl: public std::false_type { };

template<typename T, typename... Args>
struct is_constructible_impl<void_t<decltype(T(std::declval<Args>()...))>, T, Args...>: public std::true_type {};

template<typename T, typename... Args>
constexpr bool is_constructible_impl_v = is_constructible_impl<T, Args...>::value;


template<typename T, typename... Args>
struct is_constructible: public is_constructible_impl<void, T, Args...> {  };

template<typename T>
struct is_constructible<T&, T&&>: public std::false_type {  };

template<typename T>
struct is_constructible<T&&, T&>: public std::false_type {  };

template<typename T>
struct is_constructible<T&, T>: public std::false_type {  };

template<typename T, typename... Args>
constexpr bool is_constructible_v = is_constructible<T, Args...>::value;


template<typename T>
struct is_copy_constructible: is_constructible<T, add_lvalue_reference_t<add_const_t<T>>> {  };

template<typename T>
constexpr bool is_copy_constructible_v = is_copy_constructible<T>::value;
