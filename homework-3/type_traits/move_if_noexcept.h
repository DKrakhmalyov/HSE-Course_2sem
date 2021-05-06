# pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"

template<typename T >
typename conditional<
        !is_nothrow_move_constructible<T>::value && is_copy_constructible<T>::value,
        const T&,
        T&&>::value move_if_noexcept(T& x) noexcept {
    return static_cast<conditional_v<
                !is_nothrow_move_constructible<T>::value && is_copy_constructible<T>::value,
                const T&,
                T&&>>(x);
}
