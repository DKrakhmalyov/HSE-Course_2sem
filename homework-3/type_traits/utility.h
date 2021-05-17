#pragma once

#include <type_traits>

template <typename T>
struct unref {
  using type = T;
};
template <typename T>
struct unref<T&> {
  using type = T;
};
template <typename T>
struct unref<volatile T&&> {
  using type = T;
};

template <typename T>
struct uncv {
  using type = T;
};
template <typename T>
struct uncv<const T> {
  using type = T;
};
template <typename T>
struct uncv<volatile T> {
  using type = T;
};
template <typename T>
struct uncv<const volatile T> {
  using type = T;
};

template <typename T>
struct uncvref {
  using type = typename uncv<typename unref<T>::type>::type;
};

template <typename T>
using uncvref_t = typename uncvref<T>::type;

template <typename T>
struct add_const {
  using type = const T;
};

template <typename T>
using add_const_t = const T;

template <typename T>
struct add_lvalue_reference {
  using type = T&;
};

template <typename T>
struct add_rvalue_reference {
  using type = T&&;
};

template <typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

template <typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

template <typename T>
typename std::add_rvalue_reference<T>::type myDeclval() noexcept;
