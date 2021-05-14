#pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"

template<typename T>
decltype(auto) move_if_noexcept(T &&value) {
  using unveil = uncvref_t<T>;
  using lvalueRef = add_lvalue_reference_t<unveil>;
  using rvalueRef = add_rvalue_reference_t<unveil>;

  constexpr auto condition = !is_nothrow_move_constructible<unveil>();
  return static_cast<conditional_t<condition, lvalueRef, rvalueRef>>(value);
}