//
// Created by Denis on 12.03.2021.
//

#include <utility>
#include <stdexcept>
#include "static_array.h"

template<typename T, size_t sz>
static_array<T, sz>::static_array() : static_array(sz) {};

template<typename T, size_t sz>
static_array<T, sz>::static_array(size_t newSize) {
    totalSize = newSize;
    data = new T*[newSize];
    for (size_t i = 0; i < newSize; i++) {
        data[i] = nullptr;
    }
}

template<typename T, size_t sz>
static_array<T, sz>::~static_array() {
    clear();
    delete[] data;
}

template<typename T, size_t sz>
size_t static_array<T, sz>::current_size() {
    return filledCount;
}

template<typename T, size_t sz>
size_t static_array<T, sz>::size() {
    return totalSize;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, T&& obj) {
    if (data[ind] != nullptr) {
        delete data[ind];
        filledCount--;
    }
    data[ind] = new T(std::move(obj));
    filledCount++;
    if (beginPtr == nullptr) {
        beginPtr = data + ind;
    }
    if (endPtr == nullptr) {
        endPtr = data + ind + 1;
    }
    if (data + ind < beginPtr) {
        beginPtr = data + ind;
    }
    if (data + ind + 1 > endPtr) {
        endPtr = data + ind + 1;
    }
    return static_array<T, sz>::iterator(&data[ind], this);
}


template<typename T, size_t sz>
template<class... Args>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, Args&& ... args) {
    return emplace(ind, T(std::forward<Args>(args)...));
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::begin() {
    return static_array::iterator(beginPtr, this);
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator  static_array<T, sz>::end() {
    return static_array<T, sz>::iterator(endPtr, this);
}

template<typename T, size_t sz>
void static_array<T, sz>::clear() {
    for (size_t i = 0; i < totalSize; i++) {
        delete data[i];
        data[i] = nullptr;
    }
    beginPtr = endPtr = nullptr;
    filledCount = 0;
}

template<typename T, size_t sz>
void static_array<T, sz>::erase(static_array<T, sz>::iterator it) {
    if (filledCount == 1) {
        beginPtr = endPtr = nullptr;
    } else {
        if (it.ptr == beginPtr) {
            static_array<T, sz>::iterator tmp(it);
            ++tmp;
            beginPtr = tmp.ptr;
        }
        if (it.ptr == endPtr) {
            static_array<T, sz>::iterator tmp(it);
            --tmp;
            endPtr = tmp.ptr;
        }
    }
    delete *it.ptr;
    it.arr->data[it.ptr - (it.arr->data)] = nullptr;
    it.ptr = nullptr;
    filledCount--;
}

template<typename T, size_t sz>
T& static_array<T, sz>::at(size_t ind) {
    if (ind < 0 || ind >= totalSize) {
        throw std::out_of_range("out of array range");
    } else if (data[ind] == nullptr) {
        throw std::invalid_argument("element was not initialized");
    } else {
        return *data[ind];
    }
}

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator(const static_array::iterator& oth) {
    ptr = oth.ptr;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator=(const static_array::iterator& oth) {
    ptr = oth.ptr;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator++() {
    do {
        ptr++;
    } while (*ptr == nullptr && ptr < arr->endPtr);
    return *this;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator--() {
    do {
        ptr--;
    } while (*ptr == nullptr && ptr >= arr->beginPtr);
    return *this;
}

template<typename T, size_t sz>
T *static_array<T, sz>::iterator::operator->() const {
    return *ptr;
}

template<typename T, size_t sz>
T& static_array<T, sz>::iterator::operator*() const {
    return **ptr;
}

template<typename T, size_t sz>
bool static_array<T, sz>::iterator::operator==(const static_array<T, sz>::iterator &oth) {
    return ptr == oth.ptr;
}


#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
template<typename T, size_t sz>
bool static_array<T, sz>::iterator::operator!=(const static_array<T, sz>::iterator &oth) {
    return !(this == oth);
}
#pragma clang diagnostic pop

template<typename T, size_t sz>
static_array<T, sz>::iterator::~iterator() = default;

