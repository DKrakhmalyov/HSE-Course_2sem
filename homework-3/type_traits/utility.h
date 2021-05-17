# pragma once

#include <type_traits>

template<typename T> struct remove_const          { typedef T type; };
template<typename T> struct remove_const<const T> { typedef T type; };

template<typename T>
using remove_const_t = typename remove_const<T>::type;


template<typename T> struct remove_volatile             { typedef T type; };
template<typename T> struct remove_volatile<volatile T> { typedef T type; };

template<typename T>
using remove_volatile_t = typename remove_volatile<T>::type;


template<typename T> struct remove_reference      { typedef T type; };
template<typename T> struct remove_reference<T&>  { typedef T type; };
template<typename T> struct remove_reference<T&&> { typedef T type; };

template<typename T>
using remove_reference_t = typename remove_reference<T>::type;


template<typename T>
struct uncvref {
  typedef remove_const_t<remove_volatile_t<remove_reference_t<T>>> type;
};

template<typename T>
using uncvref_t = typename uncvref<T>::type;


template<typename T>
struct add_const {
  typedef const T type;
};

template<typename T>
using add_const_t = typename add_const<T>::type;

template<typename T>
struct add_lvalue_reference {
  typedef T& type;
};

template<typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

template<typename T>
struct add_rvalue_reference {
  typedef T&& type;
};

template<typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;


template<typename T>
add_rvalue_reference_t<T> declval() noexcept;


template<bool condition, typename T, typename F>
struct conditional {
  typedef T type;
};

template<typename T, typename F>
struct conditional<false, T, F> {
  typedef F type;
};

template<bool condition, typename T, typename F>
using conditional_t = typename conditional<condition, T, F>::type;
