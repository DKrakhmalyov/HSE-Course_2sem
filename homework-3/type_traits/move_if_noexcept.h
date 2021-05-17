# pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"

template<typename T> 
auto move_if_noexcept(T& arg) noexcept {
	if (is_nothrow_move_constructible<T>::value) {
		return std::move(arg);
	}
	else {
		return arg;
	}
}