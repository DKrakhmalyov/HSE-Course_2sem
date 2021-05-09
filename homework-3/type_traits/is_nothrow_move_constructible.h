#pragma once 

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"

template<typename T>
struct NoexceptObjectBuilder {
    static T object() noexcept;
};

template<typename T>
struct is_nothrow_move_constructible : conditional_t<is_constructible_v<T, add_rvalue_reference_t<T>>,
                                                     conditional_t<noexcept(std::move(T(NoexceptObjectBuilder<T>::object()))),
                                                                   std::true_type,
                                                                   std::false_type>,
                                                     std::false_type> {};

template<typename T>
constexpr bool is_nothrow_move_constructible_v = is_nothrow_move_constructible<T>::value;
