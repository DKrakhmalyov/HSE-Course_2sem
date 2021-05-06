#pragma once 

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"

//<is_constructible, is_reference, T, Args...>
template<bool, bool, typename T, typename... Args> struct is_nothrow_constructible_impl;

// is_nothrow_constructible_impl - partial specializations
//template

namespace details {
    template<typename T, typename... Args>
    auto try_nothrow_construct(int) -> conditional_v<noexcept(T(declval<Args>()...)), std::true_type, std::false_type>;
    template<typename T, typename... Args>
    auto try_nothrow_construct(...) -> std::false_type;
}

template<typename T, typename... Args>
struct is_nothrow_constructible : decltype(details::try_nothrow_construct<T, Args...>(0)) {};

//template<typename T, std::size_t N>
//struct is_nothrow_constructible<T[N]> {
//    ...
//};

template<typename T>
struct is_nothrow_move_constructible :
        is_nothrow_constructible<T, add_rvalue_reference_t<T>> {};
