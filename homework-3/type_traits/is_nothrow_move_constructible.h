#pragma once 

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"

template<typename T>
void conversion_to(T) noexcept{}

template<bool, bool, typename T, typename... Args>
struct is_nothrow_constructible_impl;

template<typename T, typename... Args>
struct is_nothrow_constructible_impl<true,false, T, Args...>:
        std::integral_constant<bool, noexcept(T(std::declval<Args>()...))>{};

template<typename T, typename Arg>
struct is_nothrow_constructible_impl<true, true, T, Arg>:
        std::integral_constant<bool, noexcept(conversion_to<T>(std::declval<Arg>()))>{};

template<typename T, typename... Args>
struct is_nothrow_constructible_impl<false, false, T, Args...> : std::false_type {};

template<typename T, typename... Args>
struct is_nothrow_constructible_impl<false, true, T, Args...> : std::false_type {};

template<typename T, typename... Args>
struct is_nothrow_constructible:
        is_nothrow_constructible_impl<is_constructible<T,Args...>::value,std::is_reference<T>::value,T,Args...>{};

template<typename T>
struct is_nothrow_move_constructible:is_nothrow_constructible<T, add_rvalue_reference_t<T>> {
};