# pragma once

#include <type_traits>

namespace std {

    template<typename T>
    struct type_identity {
        using type = T;
    };
} 

template<typename T>
struct remove_ref: public std::type_identity<T> {};

template<typename T>
struct remove_ref<T&>: public std::type_identity<T> {};

template<typename T>
struct remove_ref<T&&>: public std::type_identity<T> {};

template<typename T>
using remove_ref_t = typename remove_ref<T>::type;


template<typename T>
struct remove_const: public std::type_identity<T> {};

template<typename T>
struct remove_const<T const>: public std::type_identity<T> {};

template<typename T>
using remove_const_t = typename remove_const<T>::type;


template<typename T>
struct remove_valotile: public std::type_identity<T> {};

template<typename T>
struct remove_valotile<T volatile>: public std::type_identity<T> {};

template<typename T>
using remove_valotile_t = typename remove_valotile<T>::type;


template<typename T>
struct uncvref: public std::type_identity<remove_valotile_t<remove_const_t<remove_ref_t<T>>>> {};

template<typename T>
using uncvref_t = typename uncvref<T>::type;


template<typename T>
struct add_const: public std::type_identity<T const> {  };

template<typename T>
struct add_const<T const>: public std::type_identity<T const> {  };

template<typename T>
using add_const_t = typename add_const<T>::type;


template<typename T>
struct add_lvalue_reference: public std::type_identity<T&> {};

template<typename T>
struct add_lvalue_reference<T&>: public std::type_identity<T&> {};

template<typename T>
struct add_rvalue_reference: public std::type_identity<T&&> {};

template<typename T>
struct add_rvalue_reference<T&&>: public std::type_identity<T&&> {};

template<typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

template<typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
