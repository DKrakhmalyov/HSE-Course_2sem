//
// Created by Denis on 12.03.2021.
//

#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H

#include <stddef.h>
#include <vector>
#include <stdexcept>

template<typename T, size_t sz = 0>
class static_array {
public:
    class iterator {
    public:
        friend class static_array;

        iterator() {}

        iterator(const iterator& it) {
            *this = it;
        }

        ~iterator() {};

        bool is_null() {
            return (_index == -1 || _is_null == nullptr) ? true : (*_is_null)[_index];
        }

        iterator& operator=(const iterator& it) {
            _value = it._value;
            _index = it._index;
            _next = it._next;
            _prev = it._prev;
            return *this;
        }

        iterator& operator++() {
            do {
                *this = *this->_next;
            } while (this->is_null() && this->_next != nullptr);
            return *this;
        }

        iterator& operator--() {
            do {
                *this = *this->_prev;
            } while (this->is_null() && this->_prev != nullptr);
            return *this;
        }

        T* operator->() const {
            return _value;
        };

        T& operator*() const {
            return *_value;
        };

        friend bool operator==(const iterator& a, const iterator& b) {
            return a._index == b._index;
        };

        friend bool operator!=(const iterator& a, const iterator& b) {
            return !(a == b);
        };

    private:
        int _index = -1;
        std::vector<bool>* _is_null = nullptr;
        T* _value = nullptr;
        iterator* _next = nullptr;
        iterator* _prev = nullptr;
    };

    static_array() : static_array(sz) {};

    static_array(size_t size) {
        _is_null.assign(size, true);
        iterator* prev_it = nullptr;
        _end = new iterator();

        for (int i = 0; i < size; i++) {
            auto it = new iterator();
            it->_index = i;
            it->_is_null = &_is_null;

            if (i == size - 1) {
                it->_next = _end;
                _end->_prev = it;
            }

            if (i == 0) {
                _begin = it;
            } else {
                it->_prev = prev_it;
                prev_it->_next = it;
            }

            prev_it = it;
        }
    };

    ~static_array() {
        auto it = _begin;

        while (it->_next != nullptr) {
            erase(*it);
            auto prev = it;
            it = it->_next;
            delete prev;
        }

        delete it;
    }

    size_t current_size() {
        return _current_size;
    };

    size_t size() {
        return _is_null.size();
    };

    void clear() {
        for (auto it = _begin; it->_next != nullptr; it = it->_next) {
            erase(*it);
        }
    };

    static_array::iterator emplace(size_t ind, T&& obj) {
        auto it = _begin;
        for (int i = 0; i < ind; i++) it = it->_next;
        it->_value = new T(std::forward<T>(obj));

        if (_is_null[ind]) {
            _current_size++;
            _is_null[ind] = false;
        }

        return *it;
    };

    template<class... Args>
    static_array::iterator emplace(size_t ind, Args&&... args) {
        return emplace(ind, T(std::forward<Args>(args)...));
    };

    void erase(static_array::iterator it) {
        if (!_is_null[it._index]) {
            _current_size--;
            delete it._value;
        }
        _is_null[it._index] = true;
    };

    T& at(size_t ind) {
        if (ind >= _is_null.size()) {
            throw std::out_of_range("Given index is out of static_array range");
        }

        auto it = _begin;
        for (int i = 0; i < ind; i++) it = it->_next;
        return **it;
    };

    static_array::iterator begin() {
        return *_begin;
    };

    static_array::iterator end() {
        return *_end;
    };

private:
    size_t _current_size = 0;
    std::vector<bool> _is_null;
    iterator* _begin = nullptr;
    iterator* _end = nullptr;
};

#endif //HOMEWORK_2_STATIC_ARRAY_H
