#pragma once
#include <type_traits>
#include "utility.h"

template<typename U, typename... Args>
static decltype(U(std::declval<Args>()...)) construct(int);
template<typename U, typename... Args>
static my_void construct(...);

template<typename U> static std::true_type ref_construct(U);
template<typename U> static std::false_type ref_construct(...);

template<typename T, typename ...Args>
struct is_constructible : is_same<decltype(construct<T, Args...>(0)), T> {};

template<typename T, typename ...Args>
struct is_constructible<T&, Args...> : decltype(ref_construct<T&>(std::declval<Args>()...)) {};

template<typename T, typename ...Args>
struct is_constructible<T&&, Args...> : decltype(ref_construct<T&&>(std::declval<Args>()...)) {};


template<typename T>
struct is_copy_constructible : is_constructible<T, const T&> {};
