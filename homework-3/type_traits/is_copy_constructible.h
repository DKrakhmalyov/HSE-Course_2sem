# pragma once

#include <type_traits>

#include "utility.h"






template<typename C, typename... Args>
struct is_constructible {
private:
    template<typename...>
    static char f(...) {return 0;};

    template<typename T, typename... kwArgs>
    static decltype(T(declval<kwArgs>()... ), int()) f(int) {return 0;};


public:
    static const bool value = sizeof(f<C, Args...>(1337)) == sizeof(int);


};
template<typename T>
struct is_copy_constructible : is_constructible<T, add_lvalue_reference_t<add_const_t<T>>> {

};

template<typename T>
struct is_constructible<T &&, T &> : std::false_type {
};

