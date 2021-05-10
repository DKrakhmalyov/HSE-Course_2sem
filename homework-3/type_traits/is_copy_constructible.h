# pragma once

#include <type_traits>

#include "utility.h"

template<typename Enable, typename T, typename... Args>
struct is_constructible_impl : std::false_type {
    
};

template<typename Base, typename Derived>
struct is_invalid_base_to_derived_cast {
    static constexpr bool value = std::is_base_of<Derived, Base>::value && !std::is_base_of<Base, Derived>::value;
};

template<typename To, typename From>
struct is_invalid_lvalue_to_rvalue_cast {
    static constexpr bool value = std::is_same<typename uncvref<To>::type, typename uncvref<From>::type>::value &&
        (std::is_lvalue_reference<To>::value && !std::is_lvalue_reference<From>::value ||
         std::is_rvalue_reference<To>::value && std::is_lvalue_reference<From>::value);
};

template <typename T, typename... Args>
struct is_constructible_impl<decltype(T(declval<Args>()...), void()), T, Args...> : std::true_type {

};

template<typename T, typename... Args>
struct is_constructible {
    static constexpr bool value = is_constructible_impl<void, T, Args...>::value;
};

template<typename T, typename F>
struct is_constructible<T, F> {
    static constexpr bool value = is_constructible_impl<void, T, F>::value &&
        !is_invalid_base_to_derived_cast<T, F>::value &&
        !is_invalid_lvalue_to_rvalue_cast<T, F>::value;
};

template<typename T>
struct is_copy_constructible {
    static constexpr bool value = is_constructible<T, T>::value;
};
