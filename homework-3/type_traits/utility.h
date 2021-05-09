#pragma once

#include <type_traits>

template<bool condition, typename TrueResult, typename FalseResult>
struct conditional {
    using type = TrueResult;
};

template<typename TrueResult, typename FalseResult>
struct conditional<false, TrueResult, FalseResult> {
    using type = FalseResult;
};

template<bool condition, typename TrueResult, typename FalseResult>
using conditional_t = typename conditional<condition, TrueResult, FalseResult>::type;

template<typename T>
using void_t = void;

template<typename T>
struct add_const {
    using type = T const;
};

template<typename T>
struct add_const<T const> {
    using type = T;
};

template<typename T>
using add_const_t = typename add_const<T>::type;

template<typename T>
struct add_lvalue_reference {
    using type = T;
};

template<typename T>
struct add_lvalue_reference<T&> {
    using type = T&;
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
struct add_rvalue_reference<T&&> {
    using type = T;
};

template<typename T>
struct add_rvalue_reference<T&> {
    using type = T;
};

template<typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

template<typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

template<typename T>
struct ObjectBuilder {
    static T object();
};
