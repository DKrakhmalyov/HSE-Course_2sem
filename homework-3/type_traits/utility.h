# pragma once

#include <type_traits>

template<typename...>
using void_t = void;

template <typename T>
struct remove_cv
{
    using type = T;
};

template <typename T>
struct remove_cv<const T>
{
    using type = T;
};

template <typename T>
struct remove_cv<volatile T>
{
    using type = T;
};

template <typename T>
struct remove_cv<const volatile T>
{
    using type = T;
};

template <typename T>
struct remove_reference 
{
    using type = T;
};

template <typename T>
struct remove_reference<T&>
{
    using type = T;
};

template <typename T>
struct remove_reference<T&&>
{
    using type = T;
};

template<typename T>
using decay_t = typename remove_reference<typename remove_cv<T>::type>::type;

template<typename T>
using add_lvalue_reference_t = T&;

template<typename T>
using add_rvalue_reference_t = T&&;

template <typename T>
add_rvalue_reference_t<T> declval() noexcept;