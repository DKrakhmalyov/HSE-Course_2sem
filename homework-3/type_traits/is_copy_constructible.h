# pragma once

#include <type_traits>

#include "utility.h"

template<typename T, typename... Args>
constexpr bool is_constructible_impl(char) {
    return false;
}

template<typename T, typename... Args>
constexpr bool is_constructible_impl(decltype(T(declval<Args>()...), int())) {
    return true;
}

template<typename T, typename... Args>
struct is_constructible {
    constexpr static bool value = is_constructible_impl<T, Args...>(0);
};

template<typename T, typename F>
struct is_constructible<T, F> {
    using T_ = typename uncvref<T>::type;
    using F_ = typename uncvref<F>::type;

    constexpr static bool value = is_constructible_impl<T, F>(0) && 
        !(std::is_same_v<T_, F_> &&
         (std::is_rvalue_reference_v<T> &&  std::is_lvalue_reference_v<F> ||
          std::is_lvalue_reference_v<T> && !std::is_lvalue_reference_v<F>));
};

template<typename T>
struct is_copy_constructible {
    constexpr static bool value = is_constructible<T, const T&>::value;
};
