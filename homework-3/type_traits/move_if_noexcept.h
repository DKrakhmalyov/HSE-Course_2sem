# pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"

template<typename T>
decltype(auto) move_if_noexcept(T&& value)
{
    if constexpr (is_nothrow_move_constructible<decay_t<T>>::value)
        return std::move(std::forward<T>(value));
    else
        return std::forward<T>(value);
}