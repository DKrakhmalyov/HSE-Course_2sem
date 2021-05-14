#pragma once

#include <type_traits>

template<typename ...>
using wrap_t = void;
using empty_wrap_t = wrap_t<>;

template<typename T>
struct uncvref {
  using value = T;
};

template<typename T>
struct uncvref<const T> {
  using value = T;
};

template<typename T>
struct uncvref<volatile T> {
  using value = T;
};

template<typename T>
struct uncvref<T &> {
  using value = T;
};

template<typename T>
struct uncvref<T &&> {
  using value = T;
};

template<typename T>
using uncvref_t = typename uncvref<T>::value;

template<typename T>
struct add_const {
  using value = const T;
};

template<typename T>
using add_const_t = typename add_const<T>::value;

template<typename T>
struct add_lvalue_reference {
  using type = T &;
};

template<typename T>
struct add_rvalue_reference {
  using type = T &&;
};

template<typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

template<typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

template<bool, typename True, typename False>
struct conditional {
};

template<typename True, typename False>
struct conditional<true, True, False> {
  using type = True;
};

template<typename True, typename False>
struct conditional<false, True, False> {
  using type = False;
};

template<bool Condition, typename True, typename False>
using conditional_t = typename conditional<Condition, True, False>::type;