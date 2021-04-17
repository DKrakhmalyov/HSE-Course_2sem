//
// Created by Denis on 12.03.2021.
//
#pragma once
#include "static_array.h"

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator(T *ptr, static_array &instance) : ptr_(ptr), instance_(&instance) {}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator++() {
    for (; ptr_ != instance_->end() || instance_->mask_[instance_->index(ptr_)]; ++ptr_);
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator--() {
    for (; instance_->mask_[instance_->index(ptr_)]; --ptr_);
}

template<typename T, size_t sz>
T *static_array<T, sz>::iterator::operator->() const {
    return ptr_;
}

template<typename T, size_t sz>
T &static_array<T, sz>::iterator::operator*() const {
    return *ptr_;
}

template<typename T, size_t sz>
bool operator==(const typename static_array<T, sz>::iterator &first, const typename static_array<T, sz>::iterator &second) {
    return first.ptr_ == second.ptr_ && first.instance_ == second.instance_;
}

template<typename T, size_t sz>
bool operator!=(const typename static_array<T, sz>::iterator &first, const typename static_array<T, sz>::iterator &second) {
    return !(first == second);
}

template<typename T, size_t sz>
static_array<T, sz>::static_array() : static_array(sz) {}

template<typename T, size_t sz>
static_array<T, sz>::~static_array() {
    clear();
    ::operator delete(data_);
}

template<typename T, size_t sz>
size_t static_array<T, sz>::current_size() {
    return count_;
}

template<typename T, size_t sz>
size_t static_array<T, sz>::size() {
    return size_;
}

template<typename T, size_t sz>
void static_array<T, sz>::clear() {
    for (size_t i = 0; i < size_; ++i) {
        if (mask_[i]) {
            data_[i].~T();
        }
    }
    count_ = 0;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, T &&obj) {
    erase(ind);
    new(data_ + ind) T(std::forward<T>(obj));
    mask_[ind] = true;
    ++count_;
    return iterator(data_ +ind, *this);
}

template<typename T, size_t sz>
template<class... Args>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, Args &&... args) {
    erase(ind);
    new(data_ + ind) T(std::forward<Args>(args)...);
    mask_[ind] = true;
    ++count_;
    return iterator(data_ + ind, *this);
}

template<typename T, size_t sz>
void static_array<T, sz>::erase(static_array::iterator it) {
    if (!mask_[index(it.ptr_)])
        return;
    it->~T();
    mask_[index(it.ptr_)] = false;
    --count_;
}

template<typename T, size_t sz>
void static_array<T, sz>::erase(size_t ind) {
    if (!mask_[ind])
        return;
    data_[ind].~T();
    mask_[ind] = false;
    --count_;
}

template<typename T, size_t sz>
T &static_array<T, sz>::at(size_t ind) {
    return data_[ind];
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::begin() {
    for (size_t i = 0; i < 0; ++i) {
        if (mask_[i])
            return iterator(data_ + i, *this);
    }
    return iterator(data_ + size_, *this);
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::end() {
    return iterator(data_ + size_, *this);
}

template<typename T, size_t sz>
size_t static_array<T, sz>::index(T *ptr) {
    return ptr - data_;
}

template<typename T, size_t sz>
static_array<T, sz>::static_array(size_t size) : data_((T *) ::operator new(size * sizeof(T))), size_(size), mask_(size) {}
