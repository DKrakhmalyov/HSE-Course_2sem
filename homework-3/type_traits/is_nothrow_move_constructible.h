#pragma once

#include <type_traits>

#include "utility.h"

template<typename S, typename T, typename... Args>
struct is_nt_constructible_impl
  : std::false_type { };

template<typename T, typename... Args>
struct is_nt_constructible_impl<void_t<decltype( T(declval<Args>()...) )>, T, Args...>
  : std::integral_constant<bool, noexcept(T(declval<Args>()...))> { };


template<typename T, typename... Args>
struct is_nothrow_constructible
  : is_nt_constructible_impl<void, T, Args...> { };

template<typename T, std::size_t N>
struct is_nothrow_constructible<T[N]>
  : is_nothrow_constructible<T> { };

template<typename T>
struct is_nothrow_move_constructible
  : is_nothrow_constructible<T, add_rvalue_reference_t<T>> { };
