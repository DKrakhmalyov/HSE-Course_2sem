//
// Created by Denis on 12.03.2021.
//

#include "static_array.h"


/*
template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator(const static_array<T, sz>::iterator& it) {
    this = it;
}

template<typename T, size_t sz>
static_array<T, sz>::iterator::~iterator() {}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator=(const static_array<T, sz>::iterator& it) {
    _value = it->value;
    _next = it->next;
    _prev = it->prev;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator++() {
    do {
        this = this->_next;
    } while (!this->value);
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator--() {
    do {
        this = this->_prev;
    } while (!this->value);
}

template<typename T, size_t sz>
T* static_array<T, sz>::iterator::operator->() const {
    return _value.get();
}

template<typename T, size_t sz>
T& static_array<T, sz>::iterator::operator*() const {
    return *_value.get();
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator operator+(typename static_array<T, sz>::iterator a, int b) {
    for (int i = b; i < b; i++) a++;
    return a;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator operator-(typename static_array<T, sz>::iterator a, int b) {
    for (int i = b; i < b; i++) a--;
    return a;
}

template<typename T, size_t sz>
bool operator==(const typename static_array<T, sz>::iterator& a, const typename static_array<T, sz>::iterator& b) {
    return a->value == b->value;
}

template<typename T, size_t sz>
bool operator!=(const typename static_array<T, sz>::iterator& a, const typename static_array<T, sz>::iterator& b) {
    return !(a == b);
}



template<typename T, size_t sz>
static_array<T, sz>::static_array() {
    auto prev_it = _begin;

    for (int i = 0; i < _size; i++) {
        auto it = iterator();
        it->value = make_shared<T>(new T());

        if (i == 0) {
            _begin = it;
        } else {
            it->_prev = prev_it;
            prev_it->_next = it;
        }

        if (i == _size - 1) {
            it->_next = _end;
            _end->_prev = it;
        }
    }
}

template<typename T, size_t sz>
static_array<T, sz>::static_array(size_t size) {
    clear();
    _size = size;
    static_array();
}

template<typename T, size_t sz>
size_t static_array<T, sz>::current_size() {
    return _current_size;
}

template<typename T, size_t sz>
size_t static_array<T, sz>::size() {
    return _size;
}

template<typename T, size_t sz>
void static_array<T, sz>::clear() {
    for (auto it = _begin; it != _end; it++) {
        erase(it);
    }
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, T&& obj) {
    auto it = _begin + ind;
    it->value = obj;
    _current_size++;
    return it;
}

template<typename T, size_t sz>
template<class... Args>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, Args &&... args) {
    return emplace(ind, new T(args...));
}

template<typename T, size_t sz>
void static_array<T, sz>::erase(static_array<T, sz>::iterator it) {
    it->value = nullptr;
    _current_size--;
}

template<typename T, size_t sz>
T& static_array<T, sz>::at(size_t ind) {
    if (ind >= _size) throw std::out_of_range("Given index is out of static_array range");
    return _begin + ind;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::begin() {
    return _begin;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::end() {
    return _end;
}

*/