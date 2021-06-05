#pragma once

#include <type_traits>

#include "utility.h"


// temporary useless part

// template <typename Derived, typename Base>
// struct is_invalid_base_to_derived_cast {
    
// };

// template <typename To, typename From>
// struct is_invalid_lvalue_to_rvalue_cast : std::false_type {
    
// };

// template <typename RefTo, typename RefFrom>
// struct is_invalid_lvalue_to_rvalue_cast<RefTo &&, RefFrom &> {
    
// };

// struct is_constructible_helper {
    
// };


// solution

template <typename U, typename T, typename... Args>
struct is_constructible_impl : std::false_type {

};

template <typename T, typename... Args>
struct is_constructible_impl <
    std::void_t<decltype(T(std::declval<Args>()...))>,
    T,
    Args...
> : std::true_type {

};


// is_constructible_impl - partial specializations

template <typename T, typename... Args>
struct is_constructible : is_constructible_impl <
    void,
    T,
    Args...
> {

};

template <typename T>
struct is_constructible<T &&, T &> : std::false_type {

};

template <typename T>
struct is_copy_constructible : is_constructible <
    T,
    add_lvalue_reference_t <add_const_t<T>>
> {

};


// constants

template <typename T, typename... Args>
constexpr bool is_constructible_v = is_constructible<T, Args...>::value;

template <typename T>
constexpr bool is_copy_constructible_v = is_copy_constructible<T>::value;
