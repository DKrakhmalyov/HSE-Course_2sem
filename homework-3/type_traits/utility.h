# pragma once

#include <type_traits>

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
    using T_ = typename remove_cv<T>::type;
    using type = typename remove_reference<T_>::type;
};

template <typename T>
typename uncvref<T>::type&& declval() noexcept;