#pragma once 

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"

template<bool cond, typename T, typename... Args>
struct is_nothrow_constructible_impl : public std::false_type {};

template<typename T, typename... Args>
struct is_nothrow_constructible_impl<true, T, Args...> : std::true_type {};

template<typename T, typename... Args>
struct is_nothrow_constructible : is_nothrow_constructible_impl<noexcept(T(std::declval<Args>()...)), T, Args...> {};

template<typename T, std::size_t N>
struct is_nothrow_constructible<T[N]> : is_nothrow_constructible<T> {};

template<typename T>
struct is_nothrow_move_constructible : is_nothrow_constructible<T, add_rvalue_reference_t<T>> {};
