#pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"

template<bool, typename T, typename... Args>
struct is_nothrow_constructible_impl {
};

template<typename T, typename... Args>
struct is_nothrow_constructible_impl<true, T, Args...> : std::true_type {
};

template<typename T, typename... Args>
struct is_nothrow_constructible_impl<false, T, Args...> : std::false_type {
};

template<typename T, typename... Args>
struct is_nothrow_constructible : is_nothrow_constructible_impl<noexcept(T(std::declval<Args>()...)), T, Args...> {
};

template<typename T>
struct is_nothrow_move_constructible : is_nothrow_constructible<T, std::add_rvalue_reference_t<uncvref_t<T>>> {
};