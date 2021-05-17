# pragma once

#include <type_traits>

template<class T>
T&& declval() noexcept;



// conditional
template<bool condition, typename T, typename F>
struct conditional {
    typedef F type;
};


// conditional - partial specialization
template<typename T, typename F>
struct conditional<true, T, F> {
    typedef T type;
};

template<bool condition, typename T, typename F>
using conditional_v = typename conditional<condition, T, F>::type;


template<typename T>
struct add_const {
    using type = T;
};

template<typename T>
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
