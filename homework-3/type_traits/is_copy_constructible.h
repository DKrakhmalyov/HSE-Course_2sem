# pragma once

#include <type_traits>

#include "utility.h"

template<typename Base, typename Derived>
struct is_invalid_base_to_derived_cast {
    static constexpr bool value = 
            std::is_base_of_v<Derived, Base> &&
            !std::is_base_of_v<Base, Derived>;
};

template<typename Base, typename Derived>
constexpr bool is_invalid_base_to_derived_cast_v = is_invalid_base_to_derived_cast<Base, Derived>::value;

template<typename T, typename F>
struct is_invalid_lvalue_to_rvalue_cast 
{
    static constexpr bool value = 
        std::is_same_v<uncvref_t<T>,uncvref_t<F>> &&
        (is_lvalue_reference<T>::value && !std::is_reference_v<F> ||
        is_rvalue_reference<T>::value && is_lvalue_reference<F>::value ||
        is_lvalue_reference<T>::value && is_rvalue_reference<F>::value);
};

template<typename T, typename F>
constexpr bool is_invalid_lvalue_to_rvalue_cast_v = is_invalid_lvalue_to_rvalue_cast<T, F>::value;


template<typename T, typename... Args>
struct is_constructible_impl : std::false_type {};

template <typename T, typename... Args>
struct is_constructible_impl<decltype(T(declval<Args>()...), int()), T, Args...> : std::true_type {};


template<typename T, typename... Args>
struct is_constructible 
{
    constexpr static bool value = is_constructible_impl<T, Args...>::value;
};

template<typename T, typename F>
struct is_constructible<T, F> 
{
    constexpr static bool value = is_constructible_impl<int,T, F>::value
        && !is_invalid_lvalue_to_rvalue_cast_v<T, F>
        && !is_invalid_base_to_derived_cast_v<T, F>;
};


template<typename T>
struct is_copy_constructible {
    static constexpr bool value = is_constructible<T, T>::value;
};

template<typename T>
constexpr bool is_copy_constructible_v = is_copy_constructible<T>::value;
