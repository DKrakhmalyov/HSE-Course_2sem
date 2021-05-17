# pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"


/*
template<typename T>
decltype(auto) move_if_noexcept(T& value) {
  using type = conditional_t<!is_nothrow_move_constructible<T>::value && is_copy_constructible<T>::value,
                               add_const_t<add_lvalue_reference_t<T>>,
                               add_rvalue_reference_t<T> >;
  return static_cast<type>(value);
}
*/

template<typename T>
decltype(auto) move_if_noexcept(T& value) noexcept {
  if constexpr (!is_nothrow_move_constructible<T>::value && is_copy_constructible<T>::value)
    return static_cast<add_const_t<add_lvalue_reference_t<T>>>(value);
  else
    return static_cast<add_rvalue_reference_t<T>>(value);
}
