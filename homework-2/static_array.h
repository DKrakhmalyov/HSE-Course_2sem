//
// Created by Denis on 12.03.2021.
//
#include <cstddef>
#include <vector>
#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H

template<typename T, size_t sz = 0>
class static_array {
public:
    class iterator {
    public:
        iterator(static_array* array, T* i);
        iterator(const iterator &);

        ~iterator() = default;

        iterator &operator=(const iterator &);

        iterator &operator++();

        iterator &operator--();

        T *operator->() const;

        T &operator*() const;

        friend bool operator==(const iterator &one, const iterator &two){
            return one.ptr == two.ptr;
        }

        friend bool operator!=(const iterator &one, const iterator &two){
            return !(one == two);
        }

        T* ptr;
        static_array* father;
    };

    static_array();

    ~static_array();

    static_array(size_t size);

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
    T* arr;
    std::vector <bool> exist;
    int cur_size = 0;
    int gen_size = 0;
};

#include "static_array.cpp"
#endif //HOMEWORK_2_STATIC_ARRAY_H
