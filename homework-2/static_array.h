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

    friend class static_array;
    
    public:
        iterator() {}

        iterator(const iterator &it) {
            *this = it;
        }
        iterator(static_array<T, sz>& st) {
            this->owner = &st;
        }
        ~iterator() {     
        }

        iterator &operator=(const iterator &it) {
            value = it.value;
            next = it.next;
            prev = it.prev;
            index = it.index;
            owner = it.owner;
            return *this;
        }

        iterator &operator++() {
            *this = *(this->next);
            while (this->index != -1 && owner->is_nullptr[this->index]) {
                *this = *(this->next);
            }
            return *this;
        }

        iterator &operator--() {
            *this = *(this->prev);
            while (this->index != -1 && owner->is_nullptr[this->index]) {
                *this = *(this->prev);
            }
            return *this;
        }

        T *operator->() const {
            return value;
        }

        T &operator*() const {
            return *value;
        }

        friend bool operator==(const iterator &a, const iterator &b) {
            return a.index == b.index;
        }

        friend bool operator!=(const iterator &a, const iterator &b) {
            return !(a == b);
        }
    private:
        iterator* next = nullptr, *prev = nullptr;
        T* value = nullptr;
        int index = -1;
        static_array<T, sz>* owner;
    };
friend class iterator;

public:
    static_array() : static_array(sz) {}

    static_array(size_t size) {
        is_nullptr.assign(size, true);
        iterator* it_prev = nullptr;
        for (size_t i = 0; i < size; ++i) {
            iterator* it = new iterator(*this);
            it->index = i;
            if (i == 0) {
                _begin = it;
            }
            else if (i == size - 1) {
                _end = new iterator(*this);
                _end->prev = it;
                it->next = _end;
                it_prev->next = it;
            } else {
                it_prev->next = it;
            }
            it->prev = it_prev;
            it_prev = it;
        }
    }
    ~static_array() {
        clear();
        for (iterator* it = _begin; it != _end;) {
            it = it->next;
            delete it->prev;
        }
        delete _end;
    }
    size_t current_size() {
        return SIZE;
    }

    size_t size() {
        return is_nullptr.size();
    }

    void clear() {
        iterator* it = _begin;
        for (int i = 0; i < is_nullptr.size(); ++i) {
            erase(*it);
            it = it->next;
        }
    }

    static_array::iterator emplace(size_t ind, T &&obj) {
        iterator* it = _begin;
        for (size_t i = 0; i < ind; ++i) {
            it = it->next;
        }
        it->value = new T(std::forward<T>(obj));
        if (ind != -1 && is_nullptr[ind]) {
            SIZE++;
            is_nullptr[ind] = false;
        }
        return *it;
    }

    template<class... Args>
    static_array::iterator emplace(size_t ind, Args &&... args) {
        return emplace(ind, T(std::forward<Args>(args)...));
    }

    void erase(static_array::iterator it) {
        if (!is_nullptr[it.index]) {
            SIZE--;
            delete it.value;
        }
        is_nullptr[it.index] = true;
    }

    T& at(size_t ind) {
        if (ind >= size()) {
            throw std::out_of_range("Index is out of static_array's range");
        }
        iterator* it = _begin;
        for (size_t i = 0; i < ind; ++i) {
            it = it->next;
        }
        if (is_nullptr[it->index]) {
            throw "Uninitialized element of static_array.";
        }
        return *(it->value);
    }

    static_array::iterator begin() {
        return *(_begin);
    }

    static_array::iterator end() {
        return *(_end);
    }
private:
    size_t SIZE = 0;
    iterator* _begin = nullptr, *_end = nullptr;
    std::vector<bool> is_nullptr;
};

#endif //HOMEWORK_2_STATIC_ARRAY_H
