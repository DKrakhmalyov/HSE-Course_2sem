#include <iostream>

#include <iostream>
#include "gtest/gtest.h"
#include "static_array.h"

class A{
    A() = delete;
};

TEST(static_array, Creating) {
    static_array<int, 10> st;
}

TEST(static_array, Creating2) {
    static_array<A, 10> st;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}