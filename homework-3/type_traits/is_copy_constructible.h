# pragma once

#include <type_traits>

#include "utility.h"

template<typename, typename Type, typename... Args>
struct is_constructible_impl : std::false_type {};

template<typename Type, typename... Args>
struct is_constructible_impl<void_t<decltype(Type(ObjectBuilder<Args>::object()...))>, Type, Args...> : std::true_type {};

template<typename Type, typename... Args>
struct is_constructible : is_constructible_impl<void, Type, Args...> {};

template<typename Type>
struct is_constructible<Type&, Type> : std::false_type {};

template<typename Type>
struct is_constructible<Type&, add_rvalue_reference_t<Type>> : std::false_type {};

template<typename Type>
struct is_constructible<add_rvalue_reference_t<Type>, Type&> : std::false_type {};

template<typename Type, typename... Args>
constexpr bool is_constructible_v = is_constructible<Type, Args...>::value;
