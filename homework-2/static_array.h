//
// Created by Denis on 12.03.2021.
//

#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H

#include <cstddef>

template<typename T, size_t sz = 0>
class static_array {
public:
    class iterator {
    public:
        friend static_array<T, sz>;
        iterator(T**, int, int );

        iterator(const iterator &);

        ~iterator();

        iterator &operator=(const iterator &);

        iterator &operator++();

        iterator &operator--();

        T *operator->() const;

        T &operator*() const;

        bool operator==(iterator const &other) const;

        bool operator!=(iterator const& other) const;

        T **ptr;
        int index;
        int size;
    };

    static_array();

    explicit static_array(size_t size);

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
    T **array;
    size_t m_size;
    size_t m_current_size;
};


#endif //HOMEWORK_2_STATIC_ARRAY_H