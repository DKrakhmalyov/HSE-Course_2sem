# pragma once

#include <type_traits>

template<typename T>
struct uncvref {
    typedef T value;
};

template<typename T>
struct uncvref<const T> {
    typedef T value;
};

template<typename T>
struct uncvref<volatile T> {
    typedef T value;
};

template<typename T>
struct uncvref<const volatile T> {
    typedef T value;
};

template<typename T>
using uncvref_t = typename uncvref<T>::value;

template<typename T>
struct add_const {
    typedef const T value;
};

template<typename T>
struct add_const<const T> {
    typedef const T value;
};

template<typename T>
using add_const_t = typename add_const<T>::value;

template<typename T>
struct add_lvalue_reference {
    typedef T& value;
};

template<typename T>
struct add_rvalue_reference {
    typedef T&& value;
};

template<typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::value;

template<typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::value;

template<typename T>
struct remove_reference {
    typedef T value;
};

template<typename T>
struct remove_reference<T&> {
    typedef T value;
};

template<typename T>
struct remove_reference<T&&> {
    typedef T value;
};

template<typename T>
using remove_reference_t = typename remove_reference<T>::value;

template<bool condition, typename T, typename F>
struct conditional {
    typedef T value;
};

template<typename T, typename F>
struct conditional<false, T, F> {
    typedef F value;
};

template<bool condition, typename T, typename F>
using conditional_v = typename conditional<condition, T, F>::value;
