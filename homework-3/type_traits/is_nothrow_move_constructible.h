#pragma once

#include <type_traits>

#include "utility.h"


template<typename T, typename... Args>
struct is_nothrow_constructible {
  static constexpr bool value = noexcept( T(declval<Args>()...) );
};

template<typename T, std::size_t N>
struct is_nothrow_constructible<T[N]>
  : is_nothrow_constructible<T> { };

template<typename T>
struct is_nothrow_move_constructible
  : is_nothrow_constructible<T, add_rvalue_reference_t<T>> { };
