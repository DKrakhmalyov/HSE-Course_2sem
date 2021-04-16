//
// Created by Denis on 12.03.2021.
//

#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H

#include<utility>
#include<iostream>

#define size_t unsigned int //sorry :(

template<typename T, size_t sz = 0>
class static_array {
    T **data;
    size_t curr_size;
    size_t live_count;

public:
    class iterator {
    T **inner_pointer;
    T **end;
    T **begin;

    iterator(T **pointer, T** begin, T** end);
    public:

        iterator(const iterator &);

        ~iterator();

        iterator &operator=(const iterator &);

        iterator &operator++();

        iterator &operator--();

        T *operator->() const;

        T &operator*() const;

        bool operator==(const iterator &);

        bool operator!=(const iterator &);

        friend class static_array;
    };

    static_array();

    static_array(size_t sz1);

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

    static_array(const static_array&);

    static_array& operator =(const static_array&);

    ~static_array();

    static_array(static_array&&);

    static_array& operator =(static_array&&);  
};

#endif //HOMEWORK_2_STATIC_ARRAY_H
