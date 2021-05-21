# pragma once

#include <type_traits>

template<typename... Args>
using void_t = void;

template<typename T>
struct remove_cv {
	using type = T;
};

template<typename T>
struct remove_cv<const T> {
	using type = T;
};

template<typename T>
struct remove_cv<volatile T> {
	using type = T;
};

template<typename T>
struct remove_cv<const volatile T> {
	using type = T;
};

template<typename T>
struct remove_reference {
	using type = T;
};

template<typename T>
struct remove_reference<T&> {
	using type = T;
};

template<typename T>
struct remove_reference<T&&> {
	using type = T;
};

template<typename T>
struct uncvref {
	using _T = typename remove_cv<T>::type;
	using type = typename remove_reference<_T>::type;
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
	using type = T&;
};

template<typename T>
struct add_rvalue_reference {
	using type = T&&;
};

template<typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

template<typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
