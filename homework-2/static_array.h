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
    struct info {
        T value;
        bool used;
        info* next;
        info* before;
        int size;
        size_t index;
    };
    size_t counter_elements;
    size_t array_size;
    std::vector<info> array;
public:

    class iterator {
        friend class static_array;
    public:
        info* array_pointer;
    public:
        iterator() {
            array_pointer = nullptr;
        }

        iterator(const iterator &copy) {
            array_pointer = copy.array_pointer;
        }

        ~iterator() {
            array_pointer = nullptr;
        }

        iterator &operator=(const iterator &copy) {
            array_pointer = copy.array_pointer;
            return *this;
        }

        iterator &operator++() {
            size_t max_size = array_pointer->size;
            size_t index = array_pointer->index;
            while(true) {
                index++;
                if(index == max_size) {
                    break;
                }
                array_pointer = array_pointer->next;
                if(array_pointer->used) {
                    break;
                }
            }
            return *this;
        }

        iterator &operator--() {
            size_t index = array_pointer->index;
            for(array_pointer = array_pointer->before, index = index - 1;
                index >= 0 && !array_pointer->used;
                array_pointer = array_pointer->before, index--);
            return *this;
        }

        T *operator->() {
            return &array_pointer->value;
        }

        T &operator*()  {
            return array_pointer->value;
        }

        friend bool operator==(const iterator &first, const iterator &second) {
            if(first.array_pointer == second.array_pointer) {
                return true;
            }
            return false;
        }

        friend bool operator!=(const iterator &first, const iterator &second) {
            if(first.array_pointer != second.array_pointer) {
                return true;
            }
            return false;
        }
    };

    static_array() : static_array(sz) {}

    static_array(size_t size) {
        array.reserve(size + 1);
        for(int i = 0; i < size + 1; i++) {
            array[i].used = false;
            array[i].size = size;
            array[i].index = i;
            if(i != 0) {
                array[i].before = &array[i - 1];
                array[i - 1].next = &array[i];
            }
        }
        counter_elements = 0;
        array_size = size;
    }

    ~static_array() {
        array.clear();
    }

    size_t current_size() {
        return counter_elements;
    }

    size_t size() {
        return array_size;
    }

    void clear() {
        counter_elements = 0;
        for(int i = 0; i < array_size; i++) {
            array[i].next = array[i].before = nullptr;
            array[i].used = false;
        }
    }

    static_array::iterator emplace(size_t ind, T &&obj) {
        array[ind].index = ind;
        if(!array[ind].used) {
            counter_elements++;
            array[ind].used = true;
        }
        array[ind].value = T(std::forward<T>(obj));
        iterator it;
        it.array_pointer = &array[ind];
        return it;
    }

    template<class... Args>
    static_array::iterator emplace(size_t ind, Args &&... args) {
        return emplace(ind, T(std::forward<Args>(args)...));
    }

    void erase(static_array::iterator it) {
        if(it.array_pointer->used == true) {
            counter_elements--;
        }
        it.array_pointer->used = false;
    }

    T& at(size_t ind) {
        if(ind >= array_size || !array[ind].used) {
            throw std :: out_of_range("error: out of bounds of the array");
        }
        return array[ind].value;
    }

    static_array::iterator begin() {
        iterator it;
        for(int i = 0; i < array_size; i++) {
            if(array[i].used) {
                it.array_pointer = &array[i];
                std :: cout << array[i].value << std :: endl;
                break;
            }
        }
        return it;
    }

    static_array::iterator end() {
        iterator it;
        for(int i = array_size - 1; i > 0; i--) {
            if(array[i].used) {
                it.array_pointer = &array[i + 1];
                break;
            }
        }
        return it;
    }

};

#endif //HOMEWORK_2_STATIC_ARRAY_H

