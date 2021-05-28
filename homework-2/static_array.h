//
// Created by dikson on 16.04.2021.
//

#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H

#include <iostream>
#include <cstdio>
#include <vector>
#include <vector>
#include <array>


template<typename T, size_t sz = 0>
class static_array {
protected:
    size_t counter_elements;
    size_t arr_size;
    T* arr;
    bool* arr_used;
public:

    class iterator {
        friend class static_array;
    public:
        static_array* element;
        size_t element_ind;
        size_t max_size;
    public:
        iterator() {
            element = nullptr;
            element_ind = 0;
            max_size = 0;
        }

        iterator(const iterator& copy) {
            *this = copy;
        }

        ~iterator() {
            element = nullptr;
        }

        iterator& operator=(const iterator& copy) {
            element = copy.element;
            element_ind = copy.element_ind;
            max_size = copy.max_size;
            return *this;
        }

        iterator& operator++() {
            while (true) {
                element_ind++;
                if (element_ind >= max_size || element->arr_used[element_ind]) {
                    break;
                }
            }
            return *this;
        }

        iterator& operator--() {
            while (true) {
                element_ind--;
                if (element_ind < 0 || element->arr_used[element_ind]) {
                    break;
                }
            }
            return *this;
        }

        T* operator->() {
            return &element->arr[element_ind];
        }

        T& operator*() {
            return element->arr[element_ind];
        }

        friend bool operator==(const iterator& first, const iterator& second) {
            if (first.element == second.element && first.element_ind == second.element_ind) {
                return true;
            }
            return false;
        }

        friend bool operator!=(const iterator& first, const iterator& second) {
            if (!(first == second)) {
                return true;
            }
            return false;
        }
    };

    static_array() : static_array(sz) {}

    static_array(size_t size) {
        arr = (T*)malloc(sizeof(T) * (size + 1));
        arr_used = (bool*)malloc(sizeof(bool) * (size + 1));
        for (int i = 0; i < size; i++) { arr_used[i] = false; }
        arr_used[size] = true;
        counter_elements = 0;
        arr_size = size;
    }

    ~static_array() {
        free(arr);
        free(arr_used);
    }

    size_t current_size() {
        return counter_elements;
    }

    size_t size() {
        return arr_size;
    }

    void clear() {
        free(arr);
        free(arr_used);
        arr = (T*)malloc(sizeof(T) * (arr_size + 1));
        arr_used = (bool*)malloc(sizeof(bool) * (arr_size + 1));
        for (int i = 0; i < arr_size; i++) { arr_used[i] = false; }
        arr_used[arr_size] = true;
        counter_elements = 0;
    }

    static_array::iterator emplace(size_t ind, T&& obj) {
        if (!arr_used[ind]) {
            counter_elements++;
            arr_used[ind] = true;
        }
        arr[ind] = std::move(obj);
        iterator it;
        it.element = this;
        it.element_ind = ind;
        it.max_size = arr_size;
        return it;
    }

    template<class... Args>
    static_array::iterator emplace(size_t ind, Args &&... args) {
        return emplace(ind, T(std::forward<Args>(args)...));
    }

    void erase(static_array::iterator it) {
        if (arr_used[it.element_ind] == true) {
            counter_elements--;
        }
        arr_used[it.element_ind] = false;
    }

    T& at(size_t ind) {
        if (ind >= arr_size || !arr_used[ind]) {
            throw std::out_of_range("error: out of bounds of the array");
        }
        return arr[ind];
    }

    static_array::iterator begin() {
        iterator it;
        it.element = this;
        it.element_ind = 0;
        it.max_size = arr_size;
        while (true) {
            if (it.element_ind == it.max_size || arr_used[it.element_ind]) {
                break;
            }
            it.element_ind++;
        }
        return it;
    }

    static_array::iterator end() {
        iterator it;
        it.element = this;
        it.element_ind = arr_size;
        it.max_size = arr_size;
        return it;
    }

};

#endif //HOMEWORK_2_STATIC_ARRAY_H
