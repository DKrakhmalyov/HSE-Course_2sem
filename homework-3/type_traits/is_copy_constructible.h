# pragma once

#include "utility.h"


template<typename T, typename... Args>
struct is_constructible { 
private:
    template<class ...>
    static char f(...) { return 0; };

    template<class C, class ...CArgs> 
    static decltype(T(declval<CArgs>()...), int()) f(int x) { return 0; }
public:
    static const bool value = sizeof(f<T, Args...>(5)) == sizeof(int);

};

template<typename T>
struct is_constructible<T&&, T&> : std::false_type {
};


template<class T>
struct is_copy_constructible :
    is_constructible<T,  add_lvalue_reference<add_const<T>>> {
};


