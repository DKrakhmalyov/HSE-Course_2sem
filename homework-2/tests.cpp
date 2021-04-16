#include <iostream>

#include <iostream>
#include "gtest/gtest.h"
#include "static_array.h"

#include <vector>
#include <array>

class A {
public:
    A() = delete;

    A(const A &) = delete;

    A &operator=(const A &) = delete;

    A(A &&obj) {};

    A &operator=(A &&obj) {};

    A(std::vector<int> &&vec, int &&a, std::array<int, 5> &&b) {}
};

struct B {
    B(int n) : num(n) {}

    int getNum() { return num; };
private:
    int num;
};

TEST(static_array, Creating) {
    static_array<int, 10> st;
}

TEST(static_array, Creating2) {
    static_array<A, 10> st;
}

TEST(static_array, CountElem) {
    static_array<int> st(10);
    st.emplace(1, 13);
    st.emplace(4, 199);
    EXPECT_EQ(st.current_size(), 2);
    EXPECT_EQ(st.size(), 10);

    st.clear();
    EXPECT_EQ(st.current_size(), 0);
}

TEST(static_array, GetElem) {
    static_array<int> st(10);
    st.emplace(1, 13);
    st.emplace(4, 199);
    EXPECT_EQ(st.at(4), 199);
    try {
        st.at(8);
    }
    catch (...) {
        EXPECT_EQ(2, 2);
    }
}

TEST(static_array, complexClass) {
    static_array<A, 10> st;
    A tst({1, 2, 3}, 10, std::array<int, 5>({1, 2, 3, 4, 5}));
    st.emplace(1, std::move(tst));
    st.emplace(2, {{1, 2, 3}, 8, {1, 2, 3, 4, 5}});

    std::vector<int> vec = {2, 2, 2, 2, 2};
    std::array<int, 5> arr = {2, 2, 2, 2, 2};
    int i = 10;
    st.emplace(4, std::move(vec), std::move(i), std::move(arr));

    EXPECT_EQ(st.current_size(), 3);
}


TEST(static_array, iterator) {

    static_array<int, 10> st;
    static_array<int, 10>::iterator it1 = st.emplace(1, 13);
    auto it2 = st.emplace(4, 199);
    st.erase(it2);
    EXPECT_EQ(st.size(), 1);
    EXPECT_EQ(*it1, 13);
}

TEST(static_array, iterators) {
    static_array<int, 10> st;
    for (int i = 0; i < 10; i += 2)
        st.emplace(i, 2 * i);
    auto it = st.begin();
    for (int i = 0; i < 10, it != st.end(); i += 2) {
        EXPECT_EQ(*it, 2 * i);
        ++it;
    }
}

TEST(static_array, iteratorsfunc) {
    static_array<B> st(10);
    for (int i = 9; i >= 0; i -= 3)
        st.emplace(i, B(i * 3));
    auto it = st.end();
    for (int i = 9; i >= 0; i -= 3) {
        EXPECT_EQ(it->getNum(), i * 3);
        --it;
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}