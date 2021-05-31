# pragma once

#include <type_traits>

#include "utility.h"

template<typename, typename T, typename... Args>
struct is_constructible_impl{
    static constexpr bool value = false;
};

template<typename T, typename... Args>
struct is_constructible_impl<void<decltype(T(Args...))>, T, Args...>{
    static constexpr bool value = true;
};

template<typename T, typename... Args>
struct is_constructible<T,Args>{
    static constexpr bool value = is_constructible_impl<void, T, Args...>::value;
};

template<typename T>
struct is_constructible<add_lvalue_reference_t<T>,T>{
    static constexpr bool value = false;
};

template<typename T>
struct is_constructible<add_lvalue_reference_t<T>,add_rvalue_reference_t<T>>{
    static constexpr bool value = false;
};

template<typename T>
struct is_constructible<add_rvalue_reference_t<T>,add_lvalue_reference_t<T>>{
    static constexpr bool value = false;
};

template<typename T>
struct is_copy_constructible {
    using value = is_constructible<T,T>::value;
};
