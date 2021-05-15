#pragma once 

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"

template<bool U, typename T, typename... Args> 
struct is_nothrow_constructible_impl: public std::false_type {  };

template<typename T, typename... Args> 
struct is_nothrow_constructible_impl<true, T, Args...>: public std::true_type {  };


template<typename T, typename... Args>
struct is_nothrow_constructible : public is_nothrow_constructible_impl<noexcept(T(std::declval<Args>()...)), T, Args...> {  };

template<typename T, std::size_t N>
struct is_nothrow_constructible<T[N]>: public std::false_type {  };


template<typename T>
struct is_nothrow_move_constructible: public is_nothrow_constructible<T, add_rvalue_reference_t<T>> {  };

template<typename T>
constexpr bool is_nothrow_move_constructible_v = is_nothrow_move_constructible<T>::value;