//
// Created by Denis on 12.03.2021.
//

#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H

#include <cstddef>
#include <cstdint>
#include <utility>
#include <memory>

template<typename T, size_t sz = 0>
class static_array {
public:
    class iterator {
        /*
         * Класс итератора
         * при index == size() считается end()-итератором
         */
    public:
        iterator(T** arr, size_t index, size_t size);

        iterator(const iterator &);

        ~iterator() = default;

        iterator &operator=(const iterator &);

        iterator &operator++();

        iterator &operator--();

        T *operator->() const;

        T &operator*() const;

        bool operator==(const iterator &);

        bool operator!=(const iterator &);

        size_t index;

    private:
        size_t _size;
        T** _arr;
    };

    static_array();

    explicit static_array(size_t a_sz);

    ~static_array();

    size_t current_size();

    size_t size();

    void clear();

    static_array::iterator emplace(size_t ind, T &&obj);

    template<class... Args>
    static_array::iterator emplace(size_t ind, Args &&... args);

    void erase(static_array::iterator);

    T &at(size_t ind);

    static_array::iterator begin();

    static_array::iterator end();
private:
    size_t _size = sz;
    size_t _real_size = 0;
    T** _data;
};

#endif //HOMEWORK_2_STATIC_ARRAY_H
