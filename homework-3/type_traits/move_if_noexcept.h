# pragma once

/*
*/
#include <type_traits>
#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"



// move_if_noexcept
template<typename T>
conditional_v<is_copy_constructible<T>::value && !is_nothrow_move_constructible<T>::value, const T&, T&&> move_if_noexcept(T& x) {
    return std::move(x);
}