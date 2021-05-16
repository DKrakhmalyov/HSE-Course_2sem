# pragma once

#include <type_traits>

#include "utility.h"


struct is_constructible_helper {
    template<typename T>
    static constexpr std::true_type check(T);

    template<typename T>
    static constexpr std::false_type check(...);

    template<typename T, typename... Args>
    static constexpr auto check1(int) ->
    decltype(
    ::new T(std::declval<Args>()...), std::true_type{}
    );

    template<typename T, typename... Args>
    static constexpr auto check1(...) -> std::false_type;

//    template<typename T, typename... Args>
//    static constexpr std::true_type check1(int, T obj = {std::declval<Args>()...});
//    template<typename T, typename... Args>
//    static constexpr std::false_type check1(...);
};

template<typename T, typename... Args>
struct is_constructible_impl : std::disjunction<
        decltype(is_constructible_helper::check<T>(std::declval<Args>()...)),
        decltype(is_constructible_helper::check1<T, Args...>(0))
> {
};

template<typename T, std::size_t N, typename T1, std::size_t N1>
struct is_constructible_impl<T[N], T1[N1]> : std::false_type {
};

template<typename T, std::size_t N, typename T1, std::size_t N1>
struct is_constructible_impl<T[N], T1(&)[N1]> : std::false_type {
};

template<typename T, std::size_t N, typename T1, std::size_t N1>
struct is_constructible_impl<T[N], T1(&&)[N1]> : std::false_type {
};

template<typename T, typename... Args>
struct is_constructible : is_constructible_impl<T, Args...> {
};

template<typename T>
struct is_copy_constructible : is_constructible_impl<T, const T &> {
};
