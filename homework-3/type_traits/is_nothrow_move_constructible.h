#pragma once 

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"

template<typename T, typename... Args>
struct is_nothrow_constructible :
	std::conjunction < is_constructible<T, Args...>,
	std::conditional_t < noexcept(T(std::declval<T>())), std::true_type, std::false_type >> { };

template<typename T, std::size_t N>
struct is_nothrow_constructible<T[N]> : std::false_type {};

template<typename T>
struct is_nothrow_move_constructible : is_nothrow_constructible<T, add_rvalue_reference_t<T>> {};