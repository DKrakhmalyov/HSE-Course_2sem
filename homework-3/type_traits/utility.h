#pragma once

#include <type_traits>


// Provides the member typedef type that names T

template <typename T>
struct identity_type {
    using type = T;
};

template <typename T>
using identity_type_t = typename identity_type<T>::type;


// remove ref

template <typename T>
struct unref : identity_type<T> {

};

template <typename T>
struct unref<T&> : identity_type<T> {

};

template <typename T>
struct unref<T&&> : identity_type<T> {

};

template <typename T>
using unref_t = typename unref<T>::type;


// remove volatile

template <typename T>
struct unvolatile : identity_type<T> {

};

template <typename T>
struct unvolatile<volatile T> : identity_type<T> {
    
};

template <typename T>
using unvolatile_t = typename unvolatile<T>::type;


// remove const

template <typename T>
struct unconst : identity_type<T> {

};

template <typename T>
struct unconst<const T> : identity_type<T> {

};

template <typename T>
using unconst_t = typename unconst<T>::type;


// add const

template <typename T>    
struct add_const : identity_type<const T> {

};

template <typename T>
using add_const_t = typename add_const<T>::type;


// remove const volatile ref

template <typename T>
struct uncvref : identity_type<unvolatile_t<unconst_t<unref_t<T>>>> {

};

template <typename T>
using uncvref_t = typename uncvref<T>::type; 


// lvalue specializations

template <typename T>
struct add_lvalue_reference : identity_type<T&> {

};

template <typename T>
struct add_lvalue_reference<T&> : identity_type<T&> {

};

template <typename T>
struct add_lvalue_reference<T&&> : identity_type<T&> {

};


// rvalue specializations

template <typename T>
struct add_rvalue_reference : identity_type<T&&> {

};

template <typename T>
struct add_rvalue_reference<T&> : identity_type<T&&> {

};

template <typename T>
struct add_rvalue_reference<T&&> : identity_type<T&&> {

};


// lvalue & rvalue types

template <typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

template <typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
