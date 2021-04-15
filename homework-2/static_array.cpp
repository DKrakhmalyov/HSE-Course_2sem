#include "static_array.h"

template <typename T, size_t sz>
static_array<T, sz>::iterator::iterator(const iterator &it) {
    m_data_ptr = it.m_data_ptr;
    m_used_ptr = it.m_used_ptr;
    m_initialized_ptr = it.m_initialized_ptr;
}

template <typename T, size_t sz>
static_array<T, sz>::iterator::iterator(T *data, bool *used, bool *initialized) {
    m_data_ptr = data;
    m_used_ptr = used;
    m_initialized_ptr = initialized;
}

template <typename T, size_t sz>
static_array<T, sz>::iterator::~iterator() {
    m_data_ptr = nullptr;
    m_used_ptr = nullptr;
    m_initialized_ptr = nullptr;
}

template <typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator=(const typename static_array<T, sz>::iterator &other) {
    if (this == &other)
        return *this;

    m_data_ptr = other.m_data_ptr;
    m_used_ptr = other.m_used_ptr;
    m_initialized_ptr = other.m_initialized_ptr;
}

template <typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator++() {
    m_data_ptr++;
    m_used_ptr++;
    m_initialized_ptr++;

    while (*m_used_ptr && !(*m_initialized_ptr)) {
        m_data_ptr++;
        m_used_ptr++;
        m_initialized_ptr++;
    }

    return *this;
}

template <typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator--() {
    m_data_ptr--;
    m_used_ptr--;
    m_initialized_ptr--;
    
    while (*m_used_ptr && !(*m_initialized_ptr)) {
        m_data_ptr--;
        m_used_ptr--;
        m_initialized_ptr--;
    }

    return *this;
}

template <typename T, size_t sz>
T &static_array<T, sz>::iterator::operator*() const {
    return *m_data_ptr; 
}

template <typename T, size_t sz>
T *static_array<T, sz>::iterator::operator->() const {
    return m_data_ptr;
}

template <typename T, size_t sz>
bool operator==(const typename static_array<T, sz>::iterator &l, 
                const typename static_array<T, sz>::iterator &r) {
    return bool(l.m_data_ptr == r.m_data_ptr);
}

template <typename T, size_t sz>
bool operator!=(const typename static_array<T, sz>::iterator &l, 
                const typename static_array<T, sz>::iterator &r) {
    return bool(l.m_data_ptr != r.m_data_ptr);
}

template <typename T, size_t sz>
static_array<T, sz>::static_array() {
    m_data = (T*)malloc(sz * sizeof(T));

    m_used = new bool[sz];
    std::fill(m_used, m_used + sz, true);

    m_initialized = new bool[sz];
    std::fill(m_initialized, m_initialized + sz, false);

    m_size = sz;
    m_current_size = 0;
}

template <typename T, size_t sz>
static_array<T, sz>::static_array(size_t n_sz) {
    m_data = (T*)malloc(n_sz * sizeof(T));

    m_used = new bool[n_sz];
    std::fill(m_used, m_used + n_sz, true);

    m_initialized = new bool[n_sz];
    std::fill(m_initialized, m_initialized + n_sz, false);

    m_size = n_sz;
    m_current_size = 0;
}

template <typename T, size_t sz>
static_array<T, sz>::~static_array() {
    free(m_data);
    delete[] m_used;
    delete[] m_initialized;
}


template <typename T, size_t sz>
size_t static_array<T, sz>::current_size() {
    return m_current_size;
}

template <typename T, size_t sz>
size_t static_array<T, sz>::size() {
    return m_size;
}

template <typename T, size_t sz>
void static_array<T, sz>::clear() {
    free(m_data);
    delete[] m_used;
    delete[] m_initialized;

    m_data = (T*)malloc(m_size * sizeof(T));

    m_used = new bool[m_size];
    std::fill(m_used, m_used + m_size, true);

    m_initialized = new bool[m_size];
    std::fill(m_initialized, m_initialized + m_size, false);

    m_current_size = 0;
}

template <typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, T &&obj) {
    m_data[ind] = std::move(obj);
    m_initialized[ind] = true;

    m_current_size++;

    return static_array<T, sz>::iterator(m_data + ind, m_used + ind, m_initialized + ind);
}

template <typename T, size_t sz>
void static_array<T, sz>::erase(static_array<T, sz>::iterator it) {
    if (it.m_data_ptr < m_data || it.m_data_ptr >= m_data + m_size)
        return;

    if (m_initialized[it.m_data_ptr - m_data] == false)
        return;

    m_current_size--;
    m_initialized[it.m_data_ptr - m_data] = false;
}

template <typename T, size_t sz>
T &static_array<T, sz>::at(size_t ind) {
    if (ind >= m_size)
        throw std::out_of_range("");

    if (!m_initialized[ind])
        throw "not initialized";

    return *(m_data + ind);
}

#include <bits/stdc++.h>

template<typename T, size_t sz> 
template<typename...Args>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, Args && ...args) {
    m_data[ind] = std::move(T(std::forward<Args>(args)...));
    m_initialized[ind] = true;

    m_current_size++;

}

template <typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::begin() {
    for (size_t i = 0; i < m_size; i++)
        if (m_initialized[i] == true)
            return static_array<T, sz>::iterator(m_data + i, m_used + i, m_initialized + i);
    return static_array<T, sz>::iterator(m_data, m_used, m_initialized);
}

template <typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::end() {
    for (int i = m_size - 1; i >= 0; i--)
        if (m_initialized[i] == true)
            return static_array<T, sz>::iterator(m_data + i + 1, m_used + i + 1, m_initialized + i + 1);
    return static_array<T, sz>::iterator(m_data + m_size + 1, m_used + m_size + 1, m_initialized + m_size + 1);
}