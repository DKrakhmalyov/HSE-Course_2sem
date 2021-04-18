#pragma once
#include "static_array.h"
#include <exception>
#include <stdexcept>
#include <vector>

template<typename T, size_t sz> 
static_array<T, sz>::static_array() {
    arr = (T *) (operator new[](sizeof(T) * sz));
    exist.assign(sz, 0);
    cur_size = 0;
    gen_size = sz;
}

template<typename T, size_t sz>
static_array<T, sz>::static_array(size_t new_size) {
    arr = (T *) (operator new[](sizeof(T) * new_size));
    exist.assign(new_size, 0);
    cur_size = 0;
    gen_size = new_size;
}

template<typename T, size_t sz>
static_array<T, sz>::~static_array() {
    operator delete[](arr, sizeof(T) * gen_size);
}

template<typename T, size_t sz>
size_t static_array<T, sz>::current_size() {
    return cur_size;
}

template<typename T, size_t sz>
size_t static_array<T, sz>::size() {
    return gen_size;
}

template<typename T, size_t sz>
void static_array<T, sz>::clear() {
    for (size_t i = 0; i < gen_size; ++i) {
        if (exist[i])
            arr[i].~T();
    }
    cur_size = 0;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t i, T &&obj) {
    arr[i] = std::move(obj);
    exist[i] = true;
    ++cur_size;
    return iterator(this, arr + i);
}

template<typename T, size_t sz>
template<class... Args>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t i, Args &&... args) {
    arr[i] = T(std::forward<Args>(args)...);
    exist[i] = true;
    ++cur_size;
    return iterator(this, arr + i);
}

template<typename T, size_t sz>
T &static_array<T, sz>::at(size_t i) {
    if (i < 0 || i >= gen_size || !exist[i])
        throw std::out_of_range("you have a problem");
    else
        return arr[i];
}

template<typename T, size_t sz>
void static_array<T, sz>::erase(static_array::iterator it) {
    it.ptr->~T();
    exist[it.ptr - arr] = false;
    --cur_size;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::begin() {
    for (size_t i = 0; i < gen_size; ++i) {
        if (exist[i])
            return iterator(this, arr + i);
    }
    return iterator(this, arr + gen_size);
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::end() {
    return iterator(this, arr + gen_size);
}

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator(static_array * array, T*small_ptr) : ptr(small_ptr), father(array) {}

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator(const iterator &other_ptr) : ptr(other_ptr.ptr), father(other_ptr.father) {}


template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator=(const iterator &other) {
    if (&other == this)
        return *this;
    ptr = other.ptr;
    father = other.father;
    return *this;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator++() {
    size_t i = (size_t) (ptr - father->arr);
    ++i;
    ++ptr;
    while (!father->exist[i] && i < father->gen_size) {
        ++i, ++ptr;
    }
    return *this;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator--() {
    size_t i = (size_t) (ptr - father->arr);
    --i;
    --ptr;
    while (!father->exist[i] && i >= 0) {
        --i, --ptr;
    }
    return *this;
}

template<typename T, size_t sz>
T *static_array<T, sz>::iterator::operator->() const {
    return ptr;
}


template<typename T, size_t sz>
T &static_array<T, sz>::iterator::operator*() const {
    return *ptr;
}
