#pragma once 

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"



template<typename C>
struct is_nothrow_move_constructible {
private:
    template<typename...>

    static char f(...) {return 0;}



    template<typename T>
    static conditional_v<noexcept(T(std::move(declval<T>()))), int, char>  f(int) {return 0;}

public:
    static const bool value = sizeof(f<C>(1337)) == sizeof(int);


};