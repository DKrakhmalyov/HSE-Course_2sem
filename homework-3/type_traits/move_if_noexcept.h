# pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"

template<bool condition, typename T, typename F>
struct conditional: public std::type_identity<T> {  };

template<typename T, typename F>
struct conditional<false, T, F>: public std::type_identity<F> {  };

template<bool condition, typename T, typename F>
using conditional_t = typename conditional<condition, T, F>::type;


template<typename T>
struct actual_move_if_noexcept {
    using type = conditional_t<
        !is_nothrow_move_constructible<T>::value && is_copy_constructible<T>::value,
        const T&,
        T&& 
    >;
};

template<typename T>
using actual_move_if_noexcept_t = typename actual_move_if_noexcept<T>::type;

template<typename T>
actual_move_if_noexcept_t<T> move_if_noexcept(T&& x) {
    return static_cast<actual_move_if_noexcept_t<T>>(x);
}
