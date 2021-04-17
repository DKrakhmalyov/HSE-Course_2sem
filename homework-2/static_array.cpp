//
// Created by Denis on 12.03.2021.
//
#include "static_array.h"
#include <utility>

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator(T** ptr, int index, int size)
    : ptr(ptr), index(index), size(size) {}

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator(const iterator &other)
    : ptr(other.ptr), index(other.index), size(other.size) {}

template<typename T, size_t sz>
static_array<T, sz>::iterator::~iterator() {}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator=(const iterator &other) {
    ptr = other.ptr;
    return *this;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator++() {
    int end = size;
    for (int i = size - 1 - index; i >= 0; i--) {
        if (*(ptr + i) != nullptr) {
            end = index + i + 1;
            break;
        }
    }
    do {
        ptr++;
        index++;
    } while (*ptr == nullptr && index < end);
    return *this;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator--() {
    int begin = 0;
    for (int i = index; i >= 0; i--) {
        if (*(ptr - i) != nullptr) {
            begin = index - i;
            break;
        }
    }
    do {
        ptr--;
        index--;
    } while (*ptr == nullptr && index > begin);
    return *this;
}

template<typename T, size_t sz>
T *static_array<T, sz>::iterator::operator->() const {
    return *ptr;
}

template<typename T, size_t sz>
T &static_array<T, sz>::iterator::operator*() const {
    return **ptr;
}

template<class T, size_t sz>
bool static_array<T, sz>::iterator::operator==(static_array<T, sz>::iterator const& second) const {
    return ptr == second.ptr;
}

template<class T, size_t sz>
bool static_array<T, sz>::iterator::operator!=(static_array<T, sz>::iterator const& second) const {
    return ptr != second.ptr;
}

template<typename T, size_t sz>
static_array<T, sz>::static_array()
: m_size(sz), m_current_size(0), array(new T*[sz + 1]) {
    for (int i = 0; i <= sz; i++) {
        array[i] = nullptr;
    }
}

template<typename T, size_t sz>
static_array<T, sz>::static_array(size_t size)
: m_size(size), m_current_size(0), array(new T*[size + 1]) {
    for (int i = 0; i <= size; i++) {
        array[i] = nullptr;
    }
}

template<typename T, size_t sz>
static_array<T, sz>::~static_array() {
    for (int i = 0; i < m_size; i++)
        if (array[i] != nullptr)
            delete array[i];
    delete[] array;
}

template<typename T, size_t sz>
size_t static_array<T, sz>::current_size() {
    return m_current_size;
}

template<typename T, size_t sz>
size_t static_array<T, sz>::size() {
    return m_size;
}

template<typename T, size_t sz>
void static_array<T, sz>::clear() {
    for (size_t i = 0; i < m_size; i++) {
        if (array[i] != nullptr) {
            delete array[i];
            array[i] = nullptr;
        }
    }
    m_current_size = 0;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, T &&obj) {
    if (array[ind] != nullptr) {
        delete array[ind];
        m_current_size--;
    }
    m_current_size++;
    array[ind] = new T(std::forward<T>(obj));
    return static_array::iterator(array + ind, ind, m_size);
}

template<typename T, size_t sz>
template<class... Args>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, Args &&... args) {
    if (array[ind] != nullptr) {
        delete array[ind];
        m_current_size--;
    }
    m_current_size++;
    array[ind] = new T(std::forward<Args>(args)...);
    return static_array::iterator(array + ind, ind, m_size);
}

template<typename T, size_t sz>
void static_array<T, sz>::erase(static_array::iterator it) {
    if (*it.ptr == nullptr) return;
    m_current_size--;
    delete *it.ptr;
    *it.ptr = nullptr;
}

template<typename T, size_t sz>
T& static_array<T, sz>::at(size_t ind) {
    if (array[ind] != nullptr)
        return *array[ind];
    if (ind < 0 || ind >= sz) 
        throw("Error: index out of range");
    throw("Errow: object is not initialised");
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::begin() {
    for (size_t i = 0; i < m_size; i++)
        if (array[i] != nullptr)
            return iterator(array + i, i, m_size);
    return iterator(array, 0, m_size);
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::end() {
    for (int i = m_size - 1 ; i >= 0; i--)
        if (array[i] != nullptr)
            return iterator(array + i + 1, i + 1, m_size);
    return iterator(array, 0, m_size);
}

