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

        iterator(int index, std::vector<T*>* ptrs) : _index(index), _ptrs(ptrs) {
        }

        iterator(const iterator& it) {
            *this = it;
        }

        ~iterator() {};

        iterator& operator=(const iterator& it) {
            _index = it._index;
            _ptrs = it._ptrs;
            return *this;
        }

        iterator& operator++() {
            do {
                _index++;
            } while (_index < (*_ptrs).size() && _get_ptr() == nullptr);
            return *this;
        }

        iterator& operator--() {
            do {
                _index--;
            } while (_index >= 0 && _get_ptr() == nullptr);
            return *this;
        }

        T* operator->() const {
            return _get_ptr();
        };

        T& operator*() const {
            return *_get_ptr();
        };

        friend bool operator==(const iterator& a, const iterator& b) {
            return a._index == b._index;
        };

        friend bool operator!=(const iterator& a, const iterator& b) {
            return !(a == b);
        };

    private:
        int _index = -1;
        std::vector<T*>* _ptrs = nullptr;

        T* _get_ptr() const {
            return (*_ptrs)[_index];
        }
    };

    static_array() : static_array(sz) {};

    static_array(size_t size) {
        _ptrs.assign(size, nullptr);
    };

    ~static_array() {
        clear();
    }

    size_t current_size() {
        return _current_size;
    };

    size_t size() {
        return _ptrs.size();
    };

    void clear() {
        for (int i = 0; i < _ptrs.size(); i++) {
            _free_ptr(i);
        }
    };

    static_array::iterator emplace(size_t ind, T&& obj) {
        if (_ptrs[ind] == nullptr) {
            _current_size++;
        }

        _free_ptr(ind);
        _ptrs[ind] = new T(std::forward<T>(obj));

        return iterator(ind, &_ptrs);
    };

    template<class... Args>
    static_array::iterator emplace(size_t ind, Args&&... args) {
        return emplace(ind, T(std::forward<Args>(args)...));
    };

    void erase(static_array::iterator it) {
        _free_ptr(it._index);
    };

    T& at(size_t ind) {
        return *_ptrs[ind];
    };

    static_array::iterator begin() {
        return iterator(0, &_ptrs);
    };

    static_array::iterator end() {
        return iterator(_ptrs.size(), &_ptrs);
    };

private:
    size_t _current_size = 0;
    std::vector<T*> _ptrs;

    void _free_ptr(int i) {
        if (_ptrs[i] != nullptr) {
            _current_size--;
        }

        delete _ptrs[i];
        _ptrs[i] = nullptr;
    }
};

#endif //HOMEWORK_2_STATIC_ARRAY_H
