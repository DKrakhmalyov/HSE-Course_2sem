//
// Created by Denis on 12.03.2021.
//

#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H

#include <cstddef>
#include <algorithm>

template<typename T, std::size_t sz = 0>
class static_array {
private:
    T *values;
    bool *is_initialised;
    size_t _size = sz;
    size_t _current_size = 0;
public:
    class iterator {
    public:

        T *value;
        bool *is_initialised;

        iterator() = default;

        iterator(const iterator &it) {
            value = it.value;
            is_initialised = it.is_initialised;
        }

        iterator(T *_value, bool *_is_initialised) {
            value = _value;
            is_initialised = _is_initialised;
        }


        iterator &operator=(const iterator &it) {
            if(*this == it) {
                return *this;
            }
            value = it.value;
            is_initialised = it.is_initialised;
            return *this;
        }

        iterator &operator++() {
            value++;
            is_initialised++;
            while(!(*is_initialised)) {
                value++;
                is_initialised++;
            }
        }

        iterator &operator--() {
            value--;
            is_initialised--;
            while(!(*is_initialised)) {
                value--;
                is_initialised--;
            }
        }

        T *operator->() const {
            return value;
        }

        T &operator*() const {
            return *value;
        };

        friend bool operator==(const iterator &left, const iterator &right) {
            return left.value == right.value;
        }

        friend bool operator!=(const iterator &left, const iterator &right) {
            return left.value != right.value;
        }

    };

    static_array() {
        values = (T*) malloc(sizeof(T[sz]));
        is_initialised = (bool*) malloc(sizeof(bool[sz]));
        std::fill(is_initialised, is_initialised + sz, false);
    }

    ~static_array() {
        free(values);
        free(is_initialised);
    }

    static_array(size_t _sz) {
        values = (T*) malloc(sizeof(T[_sz]));
        is_initialised = (bool*) malloc(sizeof(bool[_sz]));
        std::fill(is_initialised, is_initialised + _sz, false);
        _size = _sz;
    }

    size_t current_size() {
        return _current_size;
    }

    size_t size() {
        return _size;
    }

    void clear() {
        free(values);
        free(is_initialised);
        values = (T*) malloc(sizeof(T[_size]));
        is_initialised = (bool*) malloc(sizeof(bool[_size]));
        std::fill(is_initialised, is_initialised + _size, false);
        _current_size = 0;
    }

    static_array::iterator emplace(size_t ind, T &&obj) {
        values[ind] = std::move(obj);
        is_initialised[ind] = true;
        _current_size++;
        return static_array::iterator(values, is_initialised);
    }

    template<class... Args>
    static_array::iterator emplace(size_t ind, Args &&... args) {
        values[ind] = std::move(T(std::forward<Args>(args)...));
        is_initialised[ind] = true;
        _current_size++;
    }

    void erase(static_array::iterator it) {
        if(it.value >= values + _size || it.value < values || !it.is_initialised) {
            return;
        }
        is_initialised[it.value - values] = false;
        _current_size--;

    }

    T &at(size_t ind) {
        if(ind < 0 || ind >= _size) {
            throw "out of range";
        }
        if(!is_initialised[ind]) {
            throw "not initialised";
        }
        return values[ind];
    }

    static_array::iterator begin() {
        for(size_t i = 0; i < _size; i++) {
            if(is_initialised[i]) {
                return static_array<T, sz>::iterator(values + i, is_initialised + i);
            }
        }
        return static_array<T, sz>::iterator(values, is_initialised);
    }

    static_array::iterator end() {
        for(int i = _size - 1; i >= 0; i--) {
            if(is_initialised[i]) {
                return static_array<T, sz>::iterator(values + i, is_initialised + i);
            }
        }
        return static_array<T, sz>::iterator();
    }
};

#endif //HOMEWORK_2_STATIC_ARRAY_H
