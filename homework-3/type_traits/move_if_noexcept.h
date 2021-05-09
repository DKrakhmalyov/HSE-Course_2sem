# pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"

template<typename T>
auto move_if_noexcept(T& x) -> decltype(auto) {
    return is_nothrow_move_constructible<T>::value ? std::move(x) : x;
};