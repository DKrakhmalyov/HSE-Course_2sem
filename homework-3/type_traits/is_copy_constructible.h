# pragma once

#include <type_traits>

#include "utility.h"

//template<typename Derived, typename Base>
//struct is_invalid_base_to_derived_cast {
//    static_assert(std::is_reference<Derived>::value, "Wrong specialization");
//    using _RawFrom = uncvref_t<Base>;
//    using _RawTo = uncvref_t<Derived>;
//    static const bool value = std::conjunction<
//            std::negation<std::is_same<_RawFrom, _RawTo>>,
//            std::is_base_of<_RawFrom, _RawTo>,
//            std::negation<is_constructible<_RawTo, Derived>>
//    >::value; //wtf is this i dont know
//};
//
//template<typename To, typename From>
//struct is_invalid_lvalue_to_rvalue_cast : std::false_type {
//    ...
//};
//
//template<typename RefTo, typename RefFrom>
//struct is_invalid_lvalue_to_rvalue_cast<RefTo &&, RefFrom &> {
//    ...
//};

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
