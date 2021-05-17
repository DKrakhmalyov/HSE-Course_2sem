# pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"

// conditional
template<bool condition, typename T, typename F>
struct conditional {
    using type = T;
};

// conditional - partial specialization

template<typename T, typename F>
struct conditional<false, T, F> {
    using type = F;
};


template<bool condition, typename T, typename F>
using conditional_t = typename conditional<condition, T, F>::type;

// move_if_noexcept

template<typename T>
struct move_if_no_except_impl {
    using type = conditional_t<!is_nothrow_move_constructible<uncvref_t<T>>::value && is_copy_constructible<uncvref_t<T>>::value, 
    add_const_t<add_lvalue_reference_t<T>>,
    add_rvalue_reference_t<T>>;
};

template<typename T>
typename move_if_no_except_impl<T>::type move_if_noexcept(T&& a) {
    return static_cast<typename move_if_no_except_impl<T>::type>(a);
}
