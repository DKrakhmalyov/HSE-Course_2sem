# pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"

template<typename T>
decltype(auto) move_if_noexcept(T&& value) {
    using clear_T = uncvref_t<T>;
    if (is_nothrow_move_constructible<clear_T>::value)
        return static_cast<add_rvalue_reference_t<clear_T>>(value);
    else
        return static_cast<add_lvalue_reference_t<clear_T>>(value);
}
