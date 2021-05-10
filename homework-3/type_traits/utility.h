# pragma once

#include <type_traits>

template<typename T>
struct remove_const {
    typedef T type;
};

template<typename T>
struct remove_const<const T> {
    typedef T type;
};

template<typename T>
using remove_const_t = typename remove_const<T>::type;

template<typename T>
struct remove_volatile {
    typedef T type;
};

template<typename T>
struct remove_volatile<volatile T> {
    typedef T type;
};

template<typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

template<typename T>
struct remove_cv {
    typedef remove_const_t<remove_volatile_t<T>> type;
};

template<typename T>
using remove_cv_t = typename remove_cv<T>::type;

template<typename T>
struct add_const {
    typedef const T type;
};

template<typename T>
using add_const_t = typename add_const<T>::type;

template<typename T>
struct add_volatile {
    typedef volatile T type;
};

template<typename T>
using add_volatile_t = typename add_const<T>::type;

template<typename T>
struct add_cv {
    typedef const volatile T type;
};

template<typename T>
struct remove_reference {
    typedef T type;
};

template<typename T>
struct remove_reference<T&> {
    typedef T type;
};

template<typename T>
struct remove_reference<T&&> {
    typedef T type;
};

template<typename T>
using remove_reference_t = typename remove_reference<T>::type;

namespace details {
    template<typename T>
    struct type_identity {
        typedef T type;
    };

    template<typename T, typename = T&>
    auto try_add_lvalue_reference(int) -> type_identity<T&>;
    template<typename T>
    auto try_add_lvalue_reference(...) -> type_identity<T>;

    template<typename T>
    auto try_add_rvalue_reference(int) -> type_identity<T&&>;
    template<typename T>
    auto try_add_rvalue_reference(...) -> type_identity<T>;
}

template<typename T>
struct add_lvalue_reference : decltype(details::try_add_lvalue_reference<T>(0)) {};

template<typename T>
struct add_rvalue_reference : decltype(details::try_add_rvalue_reference<T>(0)) {};

template<typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

template<typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

template<bool condition, typename T, typename F>
struct conditional {
    typedef T value;
};

template<typename T, typename F>
struct conditional<false, T, F> {
    typedef F value;
};

template<bool condition, typename T, typename F>
using conditional_v = typename conditional<condition, T, F>::value;

template<typename T>
add_rvalue_reference_t<T> declval() noexcept;

template<typename... T>
using void_t = void;
