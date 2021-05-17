#pragma once 

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"

namespace details {
    template<typename T, typename ...Args, typename = decltype(T(std::declval<Args>()...))>
    auto try_nothrow_construct(int) -> std::integral_constant<bool, noexcept(T(declval<Args>()...))>;
    template<typename, typename...>
    auto try_nothrow_construct(...) -> std::false_type;

    template <typename T>
    auto try_ref_nothrow_construct(T) -> std::integral_constant<bool, noexcept(T(declval<T>()))>;
    template <typename T>
    auto try_ref_nothrow_construct(...) -> std::false_type;
}

template<typename T, typename ...Args>
struct is_nothrow_constructible : decltype(details::try_nothrow_construct<T, Args...>(0)) {};

template<typename T, typename Arg>
struct is_nothrow_constructible<T&, Arg> : decltype(details::try_ref_nothrow_construct<T&>(declval<Arg>())) {};

template<typename T, typename Arg>
struct is_nothrow_constructible<T&&, Arg> : decltype(details::try_ref_nothrow_construct<T&&>(declval<Arg>())) {};

template<typename T, typename ...Args>
inline constexpr bool is_nothrow_constructible_v = typename is_nothrow_constructible<T, Args...>::value;

template<typename T>
struct is_nothrow_move_constructible : is_nothrow_constructible<T, add_rvalue_reference_t<T>> {};

template<typename T>
inline constexpr bool is_nothrow_move_constructible_v = typename is_nothrow_move_constructible<T>::value;
