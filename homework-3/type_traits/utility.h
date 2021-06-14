# pragma once

#include <type_traits>

template<typename T>
struct uncv{
    using type = T;
};

template<typename T>
struct uncv<const T>{
    using type = T;
};

template<typename T>
struct uncv<volatile T>{
    using type = T;
};

template<typename T>
struct uncv<const volatile T>{
    using type = T;
};

template<typename T>
using uncv_t = typename uncv<T>::type;

template<typename T>
struct unref{
    using type = T;
};

template<typename T>
struct unref<T&>{
    using type = T;
};

template<typename T>
struct unref<T&&>{
    using type = T;
};

template<typename T>
using unref_t = typename unref<T>::type;

template<typename T>
struct uncvref {
    using type = unref_t<uncv_t<T>>;
};

template<typename T>
using uncvref_t = typename uncvref<T>::type;

template<typename T>
struct add_const {
    using type = const T;
};

template<typename T>
using add_const_t = typename add_const<T>::type;

template<typename T>
struct add_lvalue_reference {
    using type = T&;
};

template<typename T>
struct add_rvalue_reference {
    using type = T&&;
};

template<typename T>
using add_lvalue_reference_t = T&;

template<typename T>
using add_rvalue_reference_t = T&&;

template<typename T>
add_rvalue_reference_t<T> declval() noexcept;

template<typename T>
struct is_lvalue_reference: std::false_type{};

template<typename T>
struct is_lvalue_reference<T&>: std::true_type{};

template<typename T>
struct is_rvalue_reference: std::false_type{};

template<typename T>
struct is_rvalue_reference<T&&>: std::true_type{};

template<bool B, class T, class F>
struct conditional { typedef T type; };
 
template<class T, class F>
struct conditional<false, T, F> { typedef F type; };

template<bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;