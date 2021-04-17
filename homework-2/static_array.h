//
// Created by Denis on 12.03.2021.
//

#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H

#include <cstddef>
#include <vector>

template<typename T, size_t sz = 0>
class static_array {
    T *data_;
    std::vector<bool> mask_;
    size_t size_, count_ = 0, last_ = 0;

    size_t index(T *ptr);

public:
    class iterator {
        friend static_array;

        T *ptr_;
        static_array *instance_;

    public:
        iterator(const iterator &) = default;

        iterator(T *ptr, static_array &instance);

        iterator &operator=(const iterator &) = default;

        iterator &operator++();

        iterator &operator--();

        T *operator->() const;

        T &operator*() const;

        friend bool operator==(const iterator &first, const iterator &second);

        friend bool operator!=(const iterator &first, const iterator &second);
    };

    static_array(size_t size);

    static_array();

    ~static_array();

    size_t current_size();

    size_t size();

    void clear();

    static_array::iterator emplace(size_t ind, T &&obj);

    template<class... Args>
    static_array::iterator emplace(size_t ind, Args &&... args);

    void erase(static_array::iterator it);

    void erase(size_t ind);

    T &at(size_t ind);

    static_array::iterator begin();

    static_array::iterator end();
};


#include "static_array.cpp"

#endif //HOMEWORK_2_STATIC_ARRAY_H