#pragma once

#include <algorithm>
#include <stdexcept>
#include <cassert>
#include <memory>

template<typename T, size_t size_ = 0>
class static_array
{
    using element_storage_t = std::aligned_storage_t<sizeof(T)>;

    const size_t total_capacity;
    size_t current_count;
    std::unique_ptr<element_storage_t[]> data;
    std::unique_ptr<bool[]> allocated;

    T* get_pointer(size_t index) const;
    void erase_if_exists(size_t index);
    template<typename... Args>
    static T* construct_at(T* p, Args&&... args); // available only in C++20
public:
    class iterator
    {
        static_array* container;
        size_t index;

        iterator(static_array* container, size_t index);
    public:
        iterator();

        iterator& operator++();
        iterator& operator--();
        T* operator->() const;
        T& operator*() const;
        bool operator==(const iterator& it) const;
        bool operator!=(const iterator& it) const;

        friend class static_array;
    };

    static_array();
    ~static_array();
    static_array(size_t capacity);

    size_t current_size() const;
    size_t size() const;
    void clear();
    bool valid(size_t index) const;
    T& at(size_t index);
    const T& at(size_t index) const;


    template<typename... Args>
    static_array::iterator emplace(size_t index, Args&&... args);
    static_array::iterator emplace(size_t index, T&& object);
    void erase(static_array::iterator it);

    static_array::iterator begin();
    static_array::iterator end();
};

#define STATIC_ARRAY_IMPL
#include "static_array.cpp"