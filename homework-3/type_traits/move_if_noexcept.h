# pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"

template<typename T >
decltype(auto) move_if_noexcept(T& x) noexcept {
    using return_type = conditional_v<!is_nothrow_move_constructible<T>::value && is_copy_constructible<T>::value,
            const T&, T&&>;
    return static_cast<return_type>(x);
}
