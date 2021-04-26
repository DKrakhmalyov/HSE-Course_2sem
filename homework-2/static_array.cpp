#include "static_array.h"
#include <stdexcept>

template<typename T, size_t sz>
static_array<T, sz>::static_array() : arr(sz), size_(sz) {}

template<typename T, size_t sz>
static_array<T, sz>::static_array(size_t size) : arr(size), size_(size) {}

template<typename T, size_t sz>
size_t static_array<T, sz>::current_size() {
    return this->current_size_;
}

template<typename T, size_t sz>
size_t static_array<T, sz>::size() {
    return this->size_;
}

template<typename T, size_t sz>
void static_array<T, sz>::clear() {
    this->current_size_ = 0;
    for (auto &i : this->arr) {
        i.reset();
    }
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, T &&obj) {
    if (!this->arr[ind].has_value()) {
        this->current_size_++;
    }
    this->arr[ind] = std::forward<T>(obj);
    return iterator(this, ind);
}

template<typename T, size_t sz>
template<class... Args>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, Args &&... args) {
    if (!this->arr[ind].has_value()) {
        this->current_size_++;
    }
    this->arr[ind].emplace(std::forward<Args>(args)...);
    return iterator(this, ind);
}

template<typename T, size_t sz>
void static_array<T, sz>::erase(static_array::iterator it) {
    if (this->arr[it.index].has_value()) {
        this->current_size_--;
    }
    this->arr[it.index].reset();
}

template<typename T, size_t sz>
T &static_array<T, sz>::at(size_t ind) {
    return *this->arr[ind];
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::begin() {
    for (size_t i = 0; i < this->size_; ++i) {
        if (this->arr[i].has_value()) {
            return iterator(this, i);
        }
    }
    return iterator(this, this->size_);
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::end() {
    return iterator(this, this->size_);
}

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator(static_array *container, size_t index) : container(container),
                                                                                 index(index) {}

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator(const static_array::iterator &oth) : container(oth.container),
                                                                             index(oth.index) {}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator=(const static_array::iterator &oth) {
    return iterator(oth.container, oth.index);
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator++() {
    if (this->index == this->container->size()) {
        throw std::out_of_range("Cannot increment end iterator");
    }
    do {
        this->index++;
        if (this->index < this->container->size() && this->container->arr[this->index].has_value()) {
            return *this;
        }
    } while(this->index < this->container->size());
    return *this;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator--() {
    const size_t old = this->index;
    do {
        this->index--;
        if (this->index >= 0 && this->container->arr[this->index].has_value()) {
            return *this;
        }
    } while (this->index >= 0);
    this->index = old;
    throw std::out_of_range("Cannot decrement begin iterator");
}

template<typename T, size_t sz>
T *static_array<T, sz>::iterator::operator->() const {
    return &this->container->arr[this->index].value();
}

template<typename T, size_t sz>
T &static_array<T, sz>::iterator::operator*() const {
    return *this->container->arr[this->index];
}

template<typename T, size_t sz>
inline bool static_array<T, sz>::iterator::operator==(const typename static_array<T, sz>::iterator &oth) {
    return this->index == oth.index && this->container == oth.container;
}


template<typename T, size_t sz>
inline bool static_array<T, sz>::iterator::operator!=(const typename static_array<T, sz>::iterator &oth) {
    return !(*this == oth);
}
