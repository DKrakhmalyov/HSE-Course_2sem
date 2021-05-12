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
struct conditional<true, T, F> {
    using type = T;
};

template<bool condition, typename T, typename F>
using conditional_t = typename conditional<condition, T, F>::type;

template<typename T>
struct move_if_noexcept_impl {
    using type = conditional_t<is_nothrow_move_constructible_v<uncvref_t<T>> || !is_copy_constructible_v<uncvref_t<T>>, 
                               add_rvalue_reference_t<T>, 
                               add_lvalue_reference_t<T>>;
};

template<typename T>
using move_if_noexcept_impl_t = typename move_if_noexcept_impl<T>::type;

template<typename T>
move_if_noexcept_impl_t<T> move_if_noexcept(T&& x) {
    return static_cast<move_if_noexcept_impl_t<T>>(x);
};