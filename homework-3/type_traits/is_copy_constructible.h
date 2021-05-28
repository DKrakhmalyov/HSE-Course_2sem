# pragma once

#include <type_traits>

#include "utility.h"

template<typename To, typename From>
struct is_invalid_lvalue_to_rvalue_cast 
{
    using PureTo = typename uncvref<To>::type;
    using PureFrom = typename uncvref<From>::type;

    constexpr static bool value = std::is_same_v<PureTo, PureFrom> &&
        (std::is_lvalue_reference_v<To> && !std::is_lvalue_reference_v<From> ||
         std::is_rvalue_reference_v<To> &&  std::is_lvalue_reference_v<From>);
};

template<typename T, typename... Args>
constexpr bool is_constructible_impl(decltype(T(declval<Args>()...), nullptr))
{
    return true;
}

template<typename T, typename... Args>
constexpr bool is_constructible_impl(...)
{
    return false;
}

template<typename T, typename... Args>
struct is_constructible 
{
    constexpr static bool value = is_constructible_impl<T, Args...>(nullptr);
};

template<typename T, typename F>
struct is_constructible<T, F> 
{
    constexpr static bool value = is_constructible_impl<T, F>(nullptr) && !is_invalid_lvalue_to_rvalue_cast<T, F>::value;
};

template<typename T>
struct is_copy_constructible 
{
    constexpr static bool value = is_constructible<T, const T&>::value;
};
