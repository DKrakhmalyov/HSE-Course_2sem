# pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"

template<bool condition, typename T, typename F>
struct conditional {
    using type = F;
};

template<typename T, typename F>
struct conditional<1, T, F> {
    using type = T;
};

template<bool condition, typename T, typename F>
using conditional_t = typename conditional<condition, T, F>::type;

template<typename T>
decltype(auto) move_if_noexcept(T& obj) {
    using type = conditional_t<is_nothrow_move_constructible<T>::value || !is_copy_constructible<T>::value, T&&, const T&>;
    return static_cast<type>(obj);
}
