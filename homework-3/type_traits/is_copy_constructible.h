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

    constexpr static bool lref_from_lref_ = std::is_lvalue_reference_v<T> && std::is_lvalue_reference_v<F>;
    constexpr static bool rref_from_nonlref_ = std::is_rvalue_reference_v<T> && !std::is_lvalue_reference_v<F>;
    constexpr static bool val_from_any_ = !std::is_lvalue_reference_v<T> && !std::is_rvalue_reference_v<T>;

    constexpr static bool value = std::is_same_v<T_, F_> ? (lref_from_lref_ || rref_from_nonlref_ || val_from_any_) :
        is_constructible_impl<T, F>(0);
};

template<typename T>
struct is_copy_constructible {
    constexpr static bool value = is_constructible<T, const T&>::value;
};
