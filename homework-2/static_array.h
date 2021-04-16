//
// Created by Denis on 12.03.2021.
//

#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H

#include <stddef.h>
#include <optional>
#include <stdexcept>

template<typename T, size_t sz = 0>
class static_array {
public:

    class iterator;
    friend class static_array::iterator;

    class iterator {
    public:
        friend class static_array;

        iterator() {}

        iterator(size_t index, static_array* owner) : _index(index), _owner(owner) {
        }

        iterator(const iterator& it) {
            *this = it;
        }

        ~iterator() {};

        iterator& operator=(const iterator& it) {
            _index = it._index;
            _owner = it._owner;
            return *this;
        }

        iterator& operator++() {
            do {
                _index++;
            } while (_index < _owner->size() && !_get_optional());
            return *this;
        }

        iterator& operator--() {
            do {
                _index--;
            } while (_index >= 0 && !_get_optional());
            return *this;
        }

        T* operator->() const {
            return &_get_value();
        };

        T& operator*() const {
            return _get_value();
        };

        friend bool operator==(const iterator& a, const iterator& b) {
            return a._index == b._index;
        };

        friend bool operator!=(const iterator& a, const iterator& b) {
            return !(a == b);
        };

    private:
        size_t _index = -1;
        static_array* _owner = nullptr;

        std::optional<T>& _get_optional() const {
            return _owner->_values[_index];
        }

        T& _get_value() const {
            return *_get_optional();
        }
    };

    static_array() : static_array(sz) {};

    static_array(size_t size) : _size(size) {
        _values = new std::optional<T>[_size];
    };

    ~static_array() {
        clear();
        delete[] _values;
    }

    size_t current_size() {
        return _current_size;
    };

    size_t size() {
        return _size;
    };

    void clear() {
        for (int i = 0; i < _size; i++) {
            erase(i);
        }
    };

    static_array::iterator emplace(size_t ind, T&& obj) {
        if (!_values[ind]) _current_size++;
        _values[ind] = T(std::forward<T>(obj));
        return iterator(ind, this);
    };

    template<class... Args>
    static_array::iterator emplace(size_t ind, Args&&... args) {
        return emplace(ind, T(std::forward<Args>(args)...));
    };

    void erase(int i) {
        if (!_values[i]) return;
        _current_size--;
        _values[i].reset();
    }

    void erase(static_array::iterator it) {
        erase(it._index);
    };

    T& at(size_t ind) {
        return *_values[ind];
    };

    static_array::iterator begin() {
        return iterator(0, this);
    };

    static_array::iterator end() {
        return iterator(_size, this);
    };

private:
    const size_t _size = sz;
    size_t _current_size = 0;
    std::optional<T>* _values;
};

#endif //HOMEWORK_2_STATIC_ARRAY_H
