# pragma once

#include <type_traits>

#include "utility.h"

//template<typename T, typename... Args>
//struct is_constructible_impl;
//
//template<typename Derived, typename Base>
//struct is_invalid_base_to_derived_cast {
//   ...
//};
//
//template<typename To, typename From>
//struct is_invalid_lvalue_to_rvalue_cast : std::false_type {
//    ...
//};
//
//template<typename RefTo, typename RefFrom>
//struct is_invalid_lvalue_to_rvalue_cast<RefTo&&, RefFrom&> {
//    ...
//};
//
//struct is_constructible_helper {
//    ...
//};
//
//template<typename T, typename... Args>
//struct is_constructible_impl {
//    ...
//};
//
// is_constructible_impl - partial specializations

namespace details {
    template<typename T>
    using tmp_true_type = std::true_type;

    template<typename Args>
    add_rvalue_reference_t<Args> declval() noexcept;

    template<typename T, typename... Args>
    auto try_construct(int) -> tmp_true_type<decltype(T(declval<Args>()...))>;
    template<typename T, typename... Args>
    auto try_construct(...) -> std::false_type;
}

template<typename T, typename... Args>
struct is_constructible : decltype(details::try_construct<T, Args...>(0)) {};

template<typename T>
struct is_constructible<T&&, T&> : std::false_type {};

template<typename T>
struct is_copy_constructible : is_constructible<T, add_const_t<add_lvalue_reference_t<T>>> {};
