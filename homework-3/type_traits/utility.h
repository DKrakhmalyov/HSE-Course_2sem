# pragma once
#include <type_traits>

template<typename T>
struct remove_cv
{
    using type = T;
};

template<typename T>
struct remove_cv<const T>
{
    using type = T;
};

template<typename T>
struct remove_cv<volatile T>
{
    using type = T;
};

template<typename T>
struct remove_cv<const volatile T>
{
    using type = T;
};

template<typename T>
using remove_cv_t = typename remove_cv<T>::type;

template<typename T>
struct remove_reference 
{
    using type = T;
};

template<typename T>
struct remove_reference<T&> 
{
    using type = T;
};

template<typename T>
struct remove_reference<T&&> 
{
    using type = T;
};

template<typename T>
using remove_reference_t = typename remove_reference<T>::type;

template<typename T>
struct uncvref 
{
    using type = remove_reference_t<remove_cv_t<T>>;
};

template<typename T>
using uncvref_t = typename uncvref<T>::type;

template<typename T>
using add_const_t = const T;

template<typename T>
using add_lvalue_reference_t = T&;

template<typename T>
using add_rvalue_reference_t = T&&;

template <typename T>
add_rvalue_reference_t<T> declval() noexcept;