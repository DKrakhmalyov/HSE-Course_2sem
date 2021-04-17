#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H

#include <cstddef>
#include <iostream>

template<typename T, size_t sz = 0>
class static_array {
public:

    class iterator {
    public:
        iterator(const iterator &);

        ~iterator();

        iterator &operator=(const iterator &);

        iterator &operator++();

        iterator &operator--();

        T *operator->() const;

        T &operator*() const;

        bool operator==(const static_array::iterator &);

        bool operator!=(const static_array::iterator &);

        static size_t at(size_t from, static_array<T, sz>& arr);
        static size_t at_up(size_t from, static_array<T, sz>& arr);

        size_t position();
        friend class static_array;
    private:
        iterator(size_t pos, static_array<T, sz>& arr);

        static_array<T, sz>& m_arr;
        size_t m_place;

    };

    static_array();

    static_array(size_t size);

    ~static_array();

    size_t current_size();

    size_t size();

    void clear();

    static_array::iterator emplace(size_t ind, T &&obj);

    template<class... Args>
    static_array::iterator emplace(size_t ind, Args &&... args);

    void erase(static_array::iterator);

    T &at(size_t ind);

    static_array::iterator begin();

    static_array::iterator end();

private: 
    bool* m_array_init;
    T* m_elements;
    size_t m_filled;
    size_t m_size;
    size_t m_last_element;
    
    void check_and_destroy(size_t pos);
    T& get_elem(size_t pos);
};

#endif //HOMEWORK_2_STATIC_ARRAY_H


