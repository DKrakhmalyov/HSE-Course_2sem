# pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"


// move_if_noexcept
template<class T>
struct move_if_noexcept_return_type {
    typedef conditional_v<is_nothrow_move_constructible<T>::value, T&&, T&> result;
};

template< class T >
typename move_if_noexcept_return_type<uncvref_t<T>>::result move_if_noexcept(T&& x) {
    return static_cast<typename move_if_noexcept_return_type<uncvref_t<T>>::result>(x);
};
