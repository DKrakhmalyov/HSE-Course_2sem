# pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"

template<bool condition, typename T, typename F>
struct conditional {
};

template<typename T, typename F>
struct conditional<true, T, F> {
    using type = F;
};

template<typename T, typename F>
struct conditional<false, T, F> {
    using type = T;
};

template<bool condition, typename T, typename F>
using conditional_v = typename conditional<condition, T, F>::type;

template<typename T>
conditional_v<is_nothrow_move_constructible<T>::value, uncvref_t<T>&, uncvref_t<T>&&> move_if_noexcept(T& arg){
    return static_cast<conditional_v<is_nothrow_move_constructible<T>::value, uncvref_t<T>&, uncvref_t<T>&&>>(arg);
}