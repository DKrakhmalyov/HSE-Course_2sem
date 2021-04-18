//
// Created by Denis on 12.03.2021.
//
#include <cstdlib>

#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H

template<typename T, size_t sz = 0>
class static_array {
public:
    class iterator {
    public:
        T** ptr;
        static_array<T, sz> *arr;

        iterator() = delete;

        explicit iterator(T**_ptr, static_array<T, sz> *_arr) : ptr(_ptr), arr(_arr) {};

        iterator(const iterator &);

        ~iterator();

        iterator &operator=(const iterator &);

        iterator &operator++();

        iterator &operator--();

        T *operator->() const;

        T &operator*() const;

        bool operator==(const static_array<T, sz>::iterator &);

        bool operator!=(const static_array<T, sz>::iterator &);

    };

    static_array();

    explicit static_array(size_t newSize);

    ~static_array();

    size_t current_size();

    size_t size();

    void clear();

    typename static_array<T, sz>::iterator emplace(size_t ind, T &&obj);

    template<class... Args>
    typename static_array<T, sz>::iterator emplace(size_t ind, Args &&... args);

    void erase(typename static_array<T, sz>::iterator);

    T &at(size_t ind);

    typename static_array<T, sz>::iterator begin();

    typename static_array<T, sz>::iterator end();
private:
    T **data;
    T **beginPtr = nullptr;
    T **endPtr = nullptr;
    size_t filledCount = 0;
    size_t totalSize = sz;
};

#endif //HOMEWORK_2_STATIC_ARRAY_H
