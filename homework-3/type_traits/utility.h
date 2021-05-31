# pragma once

#include <type_traits>

namespace removers{

template<typename T>
struct rem_const{
    using type = T;
};

template<typename T>
struct rem_const<const T>{
    using type = T;
};

template<typename T>
struct rem_const<volatile T>{
    using type = T;
};

template<typename T>
struct rem_const<const volatile T>{
    using type = T;
};

template<typename T>
using rem_const_t = rem_const<T>::type;

template<typename T>
struct rem_ref{
    using type = T;
};

template<typename T>
struct rem_ref<T&>{
    using type = T;
};

template<typename T>
struct rem_ref<T&&>{
    using type = T;
};

template<typename T>
using rem_ref_t = rem_ref<T>::type;

}

template<typename T>
struct uncvref {
    using type = removers::rem_ref_t<removers::rem_const_t<T>>;
};

template<typename T>
using uncvref_t = uncvref<T>::type;

template<typename T>
struct add_const {
    using type = const T;
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
using add_lvalue_reference_t = typename add_lvalue_reference<t>::type;

template<typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<t>::type;
