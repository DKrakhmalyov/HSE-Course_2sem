#pragma once 

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"

template<bool condition, class T, class F>
struct conditional { typedef T type; };

template<class T, class F>
struct conditional<false, T, F> { typedef F type; };

template< bool condition, class T, class F >
using conditional_v = typename conditional<condition, T, F>::type;


template<class T>
struct is_nothrow_move_constructible {
private:
    template<typename ...>
    static char f(...) { 
        return 0; 
    }

   template<typename C>
   static conditional_v<noexcept(C(std::declval<C&&>())), int, char> f(int) {
       return 0;
   }

public:
    static const bool value = sizeof(f<T>(5)) == sizeof(int);
};
