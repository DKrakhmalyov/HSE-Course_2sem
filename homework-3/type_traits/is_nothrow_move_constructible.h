#pragma once 

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"

template<typename, bool, typename T, typename... Args>
struct is_nothrow_constructible_impl : std::false_type {};

template<typename T, typename... Args>
struct is_nothrow_constructible_impl<void_t<decltype(T(declval<Args>()...))>, true, T, Args...> : std::true_type {};

template <class T, class... Args>
struct is_nothrow_constructible : is_nothrow_constructible_impl<void_t<>, noexcept(T(declval<Args>()...)), T, Args...> {};

/*
template<typename T, std::size_t N>
struct is_nothrow_constructible<T[N]> {
    ...
};
*/

template<typename T>
struct is_nothrow_move_constructible : is_nothrow_constructible<T, T&&> {};