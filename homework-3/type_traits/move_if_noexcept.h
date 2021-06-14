# pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"

template<typename T>
decltype(auto) move_if_noexcept(T&& value) {
    return static_cast<conditional_t<is_nothrow_move_constructible<uncvref_t<T>>::value, uncvref_t<T>&&, uncvref_t<T>&>>(value);
}