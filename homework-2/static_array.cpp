//
// Created by Denis on 12.03.2021.
//


#include "static_array.h"

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator(T **p, T **b, T **e) {
    this->inner_pointer = p;
    this->begin = b;
    this->end = e;
}

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator(const static_array<T, sz>::iterator &it) {
    this->inner_pointer = it.inner_pointer;
}


template<typename T, size_t sz>
static_array<T, sz>::iterator::~iterator() {}

template<typename T, size_t sz>
static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator=(const static_array<T, sz>::iterator &it) {
    this->inner_pointer = it.inner_pointer;
    return *this;
}

template<typename T, size_t sz >
static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator++() {
    if (this->inner_pointer != this->end) {
        this->inner_pointer++;
    }
    while (this->inner_pointer != this->end && !*this->inner_pointer) {
        ++this->inner_pointer;
    }
    return *this;
}

template<typename T, size_t sz >
static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator--() {
    if (this->inner_pointer != this->begin) {
        --this->inner_pointer;
    }
    while (this->inner_pointer != this->begin && !*this->inner_pointer) {
        --this->inner_pointer;
    }
    return *this;
}

template<typename T, size_t sz >
T *static_array<T, sz>::iterator::operator->() const {
    return *this->inner_pointer;
}

template<typename T, size_t sz >
T &static_array<T, sz>::iterator::operator*() const {
    return **this->inner_pointer;
}


template<typename T, size_t sz >
bool static_array<T, sz>::iterator::operator==(const typename static_array<T, sz>::iterator &it1) {
    return this->inner_pointer == it1.inner_pointer;
}

template<typename T, size_t sz>
bool static_array<T, sz>::iterator::operator!=(const typename static_array<T, sz>::iterator &it1) {
    return this->inner_pointer != it1.inner_pointer;
}

template<typename T, size_t sz>
static_array<T, sz>::static_array() {
    this->data = new T*[sz + 1];
    this->curr_size = sz;
    this->live_count = 0;
    for (int i = 0; i < this->curr_size; ++i) {
        this->data[i] = nullptr;
    }
}

template<typename T, size_t sz>
static_array<T, sz>::static_array(size_t sz1) {
    if (sz1 < sz) {
        sz1 = sz;
    }
    this->data = new T*[sz1 + 1]; 
    this->curr_size = sz1;
    this->live_count = 0;
    for (int i = 0; i < this->curr_size; ++i) {
        this->data[i] = nullptr;
    }
}

template<typename T, size_t sz>
size_t static_array<T, sz>::current_size() {
    return this->live_count;
}

template<typename T, size_t sz>
size_t static_array<T, sz>::size() {
    return this->curr_size;
}

template<typename T, size_t sz>
void static_array<T, sz>::clear() {
    for (int i = 0; i < this->curr_size; ++i) {
        if (this->data[i]) {
            delete this->data[i];
            this->data[i] = nullptr;
        }
    }
    delete[] this->data;
    this->data = nullptr;
    this->curr_size = 0;
    this->live_count = 0;
}


template<typename T, size_t sz>
static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, T &&obj) {
    this->live_count += (!this->data[ind]);
    this->data[ind] = new T(std::forward<T>(obj));
    return static_array<T, sz>::iterator(this->data + ind, this->data, this->data + this->curr_size);
}

template<typename T, size_t sz>
template<class... Args>
static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, Args &&... args) {
    this->live_count += (!this->data[ind]);
    this->data[ind] = new T(std::forward<Args>(args)...);
    return static_array<T, sz>::iterator(this->data + ind, this->data, this->data + this->curr_size);
}


template<typename T, size_t sz>
void static_array<T, sz>::erase(static_array<T, sz>::iterator it) {
    delete *it.inner_pointer;
    *it.inner_pointer = nullptr;
    this->live_count -= 1;
}

template<typename T, size_t sz>
T &static_array<T, sz>::at(size_t ind) {
    if (!this->data[ind]) {
        throw "hands off";
    }
    return *this->data[ind];
}

template<typename T, size_t sz>
static_array<T, sz>::iterator static_array<T, sz>::begin() {
    return static_array<T, sz>::iterator(this->data, this->data, this->data + this->curr_size);
}

template<typename T, size_t sz>
static_array<T, sz>::iterator static_array<T, sz>::end() {
    return static_array<T, sz>::iterator(this->data + this->curr_size, this->data, this->data + this->curr_size);
}

template<typename T, size_t sz>
static_array<T, sz>::static_array(const static_array<T, sz>& another) {
    this->data = new T*[another.curr_size + 1]; 
    this->curr_size = another.curr_size;
    this->live_count = another.live_count;
    for (int i = 0; i < another.curr_size; ++i) {
        this->data[i] = new T(*another.data[i]);
    } 
}

template<typename T, size_t sz>
static_array<T, sz>& static_array<T, sz>::operator=(const static_array<T, sz>& another) {
    this->clear(); 
    this->data = new T*[another.curr_size + 1]; 
    this->curr_size = another.curr_size;
    this->live_count = another.live_count;
    for (int i = 0; i < another.curr_size; ++i) {
        this->data[i] = new T(*another.data[i]);
    } 
    return *this;
}

template<typename T, size_t sz>
static_array<T, sz>::~static_array() {
    this->clear();
}

template<typename T, size_t sz>
static_array<T, sz>::static_array(static_array<T, sz>&& another) {
    this->data = another.data;
    another.data = 0;
    this.curr_size = another.curr_size;
    this.live_count = another.live_count;
}

template<typename T, size_t sz>
static_array<T, sz>& static_array<T, sz>::operator=(static_array<T, sz>&& another) {
    this->clear();
    this->data = another.data;
    another.data = 0;
    this.curr_size = another.curr_size;
    this.live_count = another.live_count;
    return *this;
}