//
// Created by Denis on 12.03.2021.
//
#pragma once
#include "static_array.h"
#include <exception>
#include <stdexcept>


template<typename T, size_t SZ>
static_array<T, SZ>::static_array() {
    mem_ptr = (T *) (operator new[](sizeof(T) * SZ));
    mask = new char[SZ / 8 + 1];
    for (size_t i = 0; i < SZ; ++i)
        set_init(i, false);
    _sz = SZ;
    _true_sz = 0;
}

template<typename T, size_t SZ>
static_array<T, SZ>::~static_array() {
    operator delete[](mem_ptr, sizeof(T) * _sz);
    delete[] mask;
}

template<typename T, size_t SZ>
static_array<T, SZ>::static_array(size_t sz) {
    mem_ptr = (T *) (operator new[](sizeof(T) * sz));
    mask = new char[sz / 8 + 1];
    for (size_t i = 0; i < sz; ++i)
        set_init(i, false);
    _sz = sz;
    _true_sz = 0;
}

template<typename T, size_t SZ>
size_t static_array<T, SZ>::current_size() {
    return _true_sz;
}

template<typename T, size_t SZ>
size_t static_array<T, SZ>::size() {
    return _sz;
}

template<typename T, size_t SZ>
void static_array<T, SZ>::clear() {
    for (size_t i = 0; i < _sz; ++i) {
        if (get_init(i)) {
            mem_ptr[i].~T();
        }
    }
    _true_sz = 0;
}

template<typename T, size_t SZ>
typename static_array<T, SZ>::iterator static_array<T, SZ>::emplace(size_t ind, T &&obj) {
    mem_ptr[ind] = std::move(obj);
    set_init(ind, true);
    ++_true_sz;
    return iterator(mem_ptr + ind, *this);
}

template<typename T, size_t SZ>
template<class... Args>
typename static_array<T, SZ>::iterator static_array<T, SZ>::emplace(size_t ind, Args &&... args) {
    mem_ptr[ind] = T(std::forward<Args>(args)...);
    set_init(ind, true);
    ++_true_sz;
    return iterator(mem_ptr + ind, *this);
}

template<typename T, size_t SZ>
T &static_array<T, SZ>::at(size_t ind) {
    if (ind < 0 || ind >= _sz || !get_init(ind))
        throw std::out_of_range("blah");
    else
        return mem_ptr[ind];
}

template<typename T, size_t SZ>
bool static_array<T, SZ>::get_init(size_t i) {
    return (mask[i / 8] >> (i % 8)) & 1;
}

template<typename T, size_t SZ>
void static_array<T, SZ>::set_init(size_t i, bool init) {
    if (init)
        mask[i / 8] |= (1 << (i % 8));
    else
        mask[i / 8] &= ~(1 << (i % 8));
}


template<typename T, size_t SZ>
void static_array<T, SZ>::erase(static_array::iterator _iterator) {
    _iterator._ptr->~T();
    set_init((size_t) (_iterator._ptr - mem_ptr), false);
    --_true_sz;
}

template<typename T, size_t SZ>
typename static_array<T, SZ>::iterator static_array<T, SZ>::begin() {
    for (size_t i = 0; i < _sz; ++i) {
        if (get_init(i))
            return iterator(mem_ptr + i, *this);
    }
    return iterator(mem_ptr + _sz, *this);
}

template<typename T, size_t SZ>
typename static_array<T, SZ>::iterator static_array<T, SZ>::end() {
    return iterator(mem_ptr + _sz, *this);
}


//iterator
template<typename T, size_t SZ>
static_array<T, SZ>::iterator::iterator(T *other_ptr, static_array &other_instance) : _ptr(other_ptr),
                                                                                      _instance(other_instance) {
}

template<typename T, size_t SZ>
static_array<T, SZ>::iterator::iterator(const iterator &other) : _ptr(other._ptr),
                                                                 _instance(other._instance) {
}


template<typename T, size_t SZ>
typename static_array<T, SZ>::iterator &static_array<T, SZ>::iterator::operator=(const iterator &other) {
    if (&other == this)
        return *this;
    _ptr = other._ptr;
    _instance = other._instance;
    return *this;
}

template<typename T, size_t SZ>
typename static_array<T, SZ>::iterator &static_array<T, SZ>::iterator::operator++() {
    size_t i = (size_t) (_ptr - _instance.mem_ptr);
    ++i;
    ++_ptr;
    while (!_instance.get_init(i) && i < _instance._sz) ++i, ++_ptr;
    return *this;
}

template<typename T, size_t SZ>
typename static_array<T, SZ>::iterator &static_array<T, SZ>::iterator::operator--() {
    size_t i = (size_t) (_ptr - _instance.mem_ptr);
    --i;
    --_ptr;
    while (!_instance.get_init(i)) --i, --_ptr;
    return *this;
}

template<typename T, size_t SZ>
T *static_array<T, SZ>::iterator::operator->() const {
    return _ptr;
}


template<typename T, size_t SZ>
T &static_array<T, SZ>::iterator::operator*() const {
    return *_ptr;
}




