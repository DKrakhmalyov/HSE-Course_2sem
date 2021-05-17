# pragma once

#include <type_traits>

#include "utility.h"


template<typename Base, typename Derived>
struct is_invalid_base_to_derived_cast{
    static constexpr bool value = std::is_base_of<Derived,Base>::value && !std::is_base_of<Base,Derived>::value;
};

template<typename U, typename T, typename... Args>
struct is_constructible_impl: std::false_type{};

template<typename T, typename... Args>
struct is_constructible_impl<std::void_t<decltype(T(std::declval<Args>()...))>,T,Args...>:
        std::true_type {};


template<typename T, typename... Args>
struct is_constructible: is_constructible_impl<void, T, Args...>{};

template<typename T, typename... Args>
constexpr bool is_constructible_v = is_constructible<T, Args...>::value;


template<typename T, typename U>
struct is_constructible<T,U>{
    static constexpr bool value = is_constructible_impl<void,T,U>::value &&
        !is_invalid_base_to_derived_cast<T,U>::value;
};

template<typename T>
struct is_constructible<T&,T&&>: std::false_type {};

template<typename T>
struct is_constructible<T&&,T&>: std::false_type {};

template<typename T>
struct is_constructible<T&,T>: std::false_type {};

template<typename T>
struct is_copy_constructible: is_constructible<add_const_t<add_lvalue_reference_t<T>>>{};
