# pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"

// conditional
template<bool condition, typename T, typename F>
struct conditional {};

template<typename T, typename F>
struct conditional<true, T, F> {
	using type = T;
};

template<typename T, typename F>
struct conditional<false, T, F> {
	using type = F;
};

template<bool condition, typename T, typename F>
using conditional_v = typename conditional<condition, T, F>::type;

// move_if_noexcept
template<typename T>
decltype(auto) move_if_noexcept(T&& value) {
	using _T = uncvref_t<T>;
	using res = conditional_v<is_nothrow_move_constructible<_T>::value, add_rvalue_reference_t<_T>, add_lvalue_reference_t<_T>>;
	return static_cast<res>(value);
}
