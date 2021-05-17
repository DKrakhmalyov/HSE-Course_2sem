# pragma once

#include <type_traits>

template<typename T>
struct TypeIdentity {
    using type = T;
};


template<typename T>
struct uncv : TypeIdentity<T> {};

template<typename T>
struct uncv<const T> : TypeIdentity<T> {};

template<typename T>
struct uncv<volatile T> : TypeIdentity<T> {};

template<typename T>
struct uncv<const volatile T> : TypeIdentity<T> {};

template<typename T>
using uncv_t = typename uncv<T>::type;


template<typename T>
struct unref : TypeIdentity<T> {};

template<typename T>
struct unref<T&> : TypeIdentity<T> {};

template<typename T>
struct unref<T&&> : TypeIdentity<T> {};

template<typename T>
using unref_t = typename unref<T>::type;


template<typename T>
struct uncvref : TypeIdentity<uncv_t<unref_t<T>>> {};

template<typename T>
using uncvref_t = typename uncvref<T>::type;



template<typename T>
struct add_const : TypeIdentity<const T> {};

template<typename T>
using add_const_t = typename add_const<T>::type;



template<typename T>
struct add_lvalue_reference : TypeIdentity<T&> {};

template<typename T>
struct add_lvalue_reference<T&> : TypeIdentity<T&> {};

template<typename T>
struct add_lvalue_reference<T&&> : TypeIdentity<T&> {};



template<typename T>
struct add_rvalue_reference : TypeIdentity<T&&> {};

template<typename T>
struct add_rvalue_reference<T&> : TypeIdentity<T&&> {};

template<typename T>
struct add_rvalue_reference<T&&> : TypeIdentity<T&&> {};



template<typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type; 

template<typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
