# pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"

template<typename T>
conditional_t<is_nothrow_move_constructible_v<T>, add_rvalue_reference_t<T>, add_lvalue_reference_t<add_const_t<T>>>
move_if_noexcept(T& argument) noexcept {
    if constexpr (is_nothrow_move_constructible_v<T>) {
        return std::move(argument);
    } else {
        return argument;
    }
}
