# pragma once

#include <type_traits>
#include <iostream>

template<class T>
T&& declval() noexcept;

template<typename T>
struct uncvref {
    typedef T result;
};

template<typename T>
struct uncvref<T&> {
    typedef T result;
};

template<typename T>
struct uncvref<T&&> {
    typedef T result;
};

template<typename T>
struct uncvref<const T> {
    typedef T result;
};

template<typename T>
struct uncvref<volatile T> {
    typedef T result;
};

template<typename T>
using uncvref_t = typename uncvref<T>::result;


template<typename T>
struct add_const {
    typedef const T type;
};

template <typename T>
struct type_identity { 
    using type = T; 
};


template< class T >
using add_const_t = typename add_const<T>::type;

template<typename T>
struct add_lvalue_reference {
    using type = T&;
};

template<typename T>
struct add_lvalue_reference<T&> {
    using type = T;
};

template<typename T>
struct add_lvalue_reference<T&&> {
    using type = T&;
};

template<typename T>
struct add_rvalue_reference {
    using type = T&&;
};

template<typename T>
struct add_rvalue_reference<T&> {
    using type = T&&;
};

template<typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

template<typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
