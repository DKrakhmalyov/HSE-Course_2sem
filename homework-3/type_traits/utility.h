# pragma once

#include <type_traits>

template<typename T>
struct uncvref {
    using value = T;
};

template<typename T>
struct uncvref<const T> {
    using value = T;
};

template<typename T>
struct uncvref<volatile T> {
    using value = T;
};

template<typename T>
struct uncvref<const volatile T> {
    using value = T;
};

template<typename T>
using uncvref_t = typename uncvref<T>::value;

template<typename T>
struct add_const {
    using value = const T;
};

template<typename T>
using add_const_t = typename add_const<T>::value;

template<typename T>
struct add_lvalue_reference {
    using type = T;
};

template<typename T>
struct add_lvalue_reference<T&> {
    using type = T&;
};

template<typename T>
struct add_rvalue_reference {
    using type = T;
};

template<typename T>
struct add_rvalue_reference<T&&> {
    using type = T&&;
};

template<typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T&>::type;

template<typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T&&>::type;

template<bool condition, typename T, typename F>
struct conditional {
    using value = T;
};

template<typename T, typename F>
struct conditional<false, T, F> {
    using value = F;
};

template<bool condition, typename T, typename F>
using conditional_v = typename conditional<condition, T, F>::value;

template <class...>
using void_t = void;

template<class T>
add_rvalue_reference_t<T> declval() noexcept;