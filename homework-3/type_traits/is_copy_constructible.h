# pragma once

#include <type_traits>

#include "utility.h"

/*template<typename T, typename... Args>
struct is_constructible_impl {
    typename value = constexpr(std::conjunction<std::is_same<decltype<T(Args)..., T> ? std::true_type : std::false_type>);
};*/

//template<typename Derived, typename Base>
//struct is_invalid_base_to_derived_cast {
//   ...
//};
//
//template<typename To, typename From>
//struct is_invalid_lvalue_to_rvalue_cast : std::false_type {
//    ...
//};

//template<typename RefTo, typename RefFrom>
//struct is_invalid_lvalue_to_rvalue_cast<RefTo&&, RefFrom&> {
//    ...
//};
//
//struct is_constructible_helper {
//    ...
//};

struct fake_object {};

// normal
template<typename T, typename... Args>
static decltype(T(std::declval<Args>()...)) construct(int);

template<typename T, typename... Args>
static fake_object construct(...);

// ref

template<typename T>
static std::true_type construct_ref(T) noexcept;

template<typename T>
static std::false_type construct_ref(...) noexcept;

template<typename T, typename... Args>
struct is_constructible : std::is_same <decltype(construct<T, Args...>(228)), T> { };

template <typename T>
struct is_constructible<T&, T> : std::false_type {};

template<typename T>
struct is_constructible<T&, T&&> : std::false_type {}; // decltype(construct_ref<T&>(get_object<Args>::value()...)) {};

template<typename T>
struct is_constructible<T&&, T&> : std::false_type {}; // decltype(construct_ref<T&&>(get_object<Args>::value()...)) {};

template<typename T>
struct is_copy_constructible : is_constructible<T, const T&> {};
