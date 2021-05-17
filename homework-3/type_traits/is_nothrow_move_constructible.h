#pragma once 

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"

//<is_constructible, is_reference, T, Args...>
template<bool, typename T, typename... Args> 
struct is_nothrow_constructible_impl : std::false_type {};

// is_nothrow_constructible_impl - partial specializations
template<typename T, typename... Args> 
struct is_nothrow_constructible_impl<true, T, Args...> : std::true_type {};

template<typename T, typename... Args>
struct is_nothrow_constructible : is_nothrow_constructible_impl<noexcept(T(std::declval<Args>()...)), T, Args...> {};

template<typename T>
struct is_nothrow_move_constructible : is_nothrow_constructible<T, add_rvalue_reference_t<T>> {};