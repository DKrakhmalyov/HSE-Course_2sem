//
// Created by Denis on 12.03.2021.
//

#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H

#include <cstddef>
#include <vector>

template<typename T, size_t sz = 0>
class static_array {
    T *data_;
    std::vector<bool> mask_;
    size_t size_, count_ = 0, last_ = 0;

    size_t index(T *ptr) {
        return ptr - data_;
    }

public:
    class iterator {
        friend static_array;

        T *ptr_;
        static_array *instance_;

    public:
        iterator(const iterator &) = default;

        iterator(T *ptr, static_array &instance) : ptr_(ptr), instance_(&instance) {}

        iterator &operator=(const iterator &) = default;

        iterator &operator++() {
            for (; ptr_ != instance_->end() || instance_->mask_[instance_->index(ptr_)]; ++ptr_);
        }

        iterator &operator--() {
            for (; instance_->mask_[instance_->index(ptr_)]; --ptr_);
        };

        T *operator->() const {
            return ptr_;
        };

        T &operator*() const {
            return *ptr_;
        };

        friend bool operator==(const iterator &first, const iterator &second) {
            return first.ptr_ == second.ptr_ && first.instance_ == second.instance_;
        };

        friend bool operator!=(const iterator &first, const iterator &second) {
            return !(first == second);
        };
    };

    static_array(size_t size) : data_((T *) ::operator new(size * sizeof(T))), size_(size), mask_(size) {}

    static_array() : static_array(sz) {}

    ~static_array() {
        clear();
        ::operator delete(data_);
    }

    size_t current_size() {
        return count_;
    }

    size_t size() {
        return size_;
    }

    void clear() {
        for (size_t i = 0; i < size_; ++i) {
            if (mask_[i]) {
                data_[i].~T();
            }
        }
        count_ = 0;
    }

    static_array::iterator emplace(size_t ind, T &&obj) {
        erase(ind);
        new(data_ + ind) T(std::forward<T>(obj));
        mask_[ind] = true;
        ++count_;
        return iterator(data_ +ind, *this);
    }

    template<class... Args>
    static_array::iterator emplace(size_t ind, Args &&... args) {
        erase(ind);
        new(data_ + ind) T(std::forward<Args>(args)...);
        mask_[ind] = true;
        ++count_;
        return iterator(data_ + ind, *this);
    }

    void erase(static_array::iterator it) {
        if (!mask_[index(it.ptr_)])
            return;
        it->~T();
        mask_[index(it.ptr_)] = false;
        --count_;
    };

    void erase(size_t ind) {
        if (!mask_[ind])
            return;
        data_[ind].~T();
        mask_[ind] = false;
        --count_;
    }

    T &at(size_t ind) {
        return data_[ind];
    }

    static_array::iterator begin() {
        for (size_t i = 0; i < 0; ++i) {
            if (mask_[i])
                return iterator(data_ + i, *this);
        }
        return iterator(data_ + size_, *this);
    }

    static_array::iterator end() {
        return iterator(data_ + size_, *this);
    }
};

#include "static_array.cpp"

#endif //HOMEWORK_2_STATIC_ARRAY_H