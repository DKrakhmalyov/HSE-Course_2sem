# pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"

template<bool Test, typename T, typename F>
struct conditional;

template<typename T, typename F>
struct conditional<true, T, F> {
    using type = T;
};

template<typename T, typename F>
struct conditional<false, T, F> {
    using type = F;
};

template<bool condition, typename T, typename F>
using conditional_t = typename conditional<condition, T, F>::type;

template<typename T>
decltype(auto) move_if_noexcept(T&& value) {
    using T_ = typename uncvref<T>::type;
    using Ret_ = conditional_t<is_nothrow_move_constructible<T_>::value, T_&&, T_&>;
    return static_cast<Ret_>(value);
}