#pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"

template <typename T, typename... Args>
struct is_nothrow_constructible_impl
    : std::integral_constant<bool, noexcept(T(myDeclval<Args>()...))> {};

template <typename T, typename Arg>
struct is_nothrow_constructible_impl<T, Arg>
    : std::integral_constant<bool, noexcept(static_cast<T>(myDeclval<Arg>()))> {};

template <typename T, typename... Args>
struct is_nothrow_constructible: is_nothrow_constructible_impl<T, Args...>{};

template <typename T, std::size_t N>
struct is_nothrow_constructible<T[N]>: is_nothrow_constructible_impl<T> {
};

template <typename T>
struct is_nothrow_move_constructible: is_nothrow_constructible_impl<T, typename unref<T>::type&&> {
};