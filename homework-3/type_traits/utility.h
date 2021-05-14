# pragma once

#include <type_traits>

namespace detail {

    template<class T>
    struct type_identity {
        using type = T;
    };

    template<class T>
    auto try_add_lvalue_reference(int) -> type_identity<T &>;

    template<class T>
    auto try_add_lvalue_reference(...) -> type_identity<T>;

    template<class T>
    auto try_add_rvalue_reference(int) -> type_identity<T &&>;

    template<class T>
    auto try_add_rvalue_reference(...) -> type_identity<T>;

}

template<class T>
struct add_lvalue_reference : decltype(detail::try_add_lvalue_reference<T>(0)) {
};

template<class T>
struct add_rvalue_reference : decltype(detail::try_add_rvalue_reference<T>(0)) {
};

template<class T>
struct remove_reference {
    using type = T;
};

template<class T>
struct remove_reference<T &> {
    using type = T;
};

template<class T>
struct remove_reference<T &&> {
    using type = T;
};

template<typename T>
using remove_reference_t = typename remove_reference<T>::type;

template<class T>
struct remove_cv {
    using type = T;
};

template<class T>
struct remove_cv<const T> {
    using type = T;
};

template<class T>
struct remove_cv<volatile T> {
    using type = T;
};

template<class T>
struct remove_cv<const volatile T> {
    using type = T;
};

template<typename T>
using remove_cv_t = typename remove_cv<T>::type;


template<typename T>
struct uncvref {
    using type = remove_cv_t<remove_reference_t<T>>;
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
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

template<typename T>
using add_rvalue_reference_t = typename add_lvalue_reference<T>::type;
