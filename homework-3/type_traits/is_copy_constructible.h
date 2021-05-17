#pragma once

#include <type_traits>

#include "utility.h"

namespace details {
    template<typename T, typename ...Args, typename = decltype(T(declval<Args>()...))>
    auto try_construct(int) -> std::true_type;
    template<typename, typename...>
    auto try_construct(...) -> std::false_type;

    template <typename T>
    auto try_ref_construct(T) -> std::true_type;
    template <typename T>
    auto try_ref_construct(...) -> std::false_type;
}

template<typename T, typename ...Args>
struct is_constructible : decltype(details::try_construct<T, Args...>(0)) {};

template<typename T, typename Arg>
struct is_constructible<T&, Arg> : decltype(details::try_ref_construct<T&>(declval<Arg>())) {};

template<typename T, typename Arg>
struct is_constructible<T&&, Arg> : decltype(details::try_ref_construct<T&&>(declval<Arg>())) {};

template<typename T, typename ...Args>
inline constexpr bool is_constructible_v = typename is_constructible<T, Args...>::value;

template<typename T>
struct is_copy_constructible : is_constructible<T, add_lvalue_reference_t<T>> {};

template<typename T>
inline constexpr bool is_copy_constructible_v = typename is_copy_constructible<T>::value;
