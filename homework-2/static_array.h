#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H

#include <iostream>
#include <stddef.h>

template <typename T, size_t sz = 0>
class static_array
{

public:
    class iterator
    {
    public:
        friend class static_array;

        iterator(const iterator&);
        ~iterator();

        iterator &operator=(const iterator&);

        iterator &operator++();

        iterator &operator--();

        T *operator->() const;

        T &operator*() const;

        bool operator==(const iterator&);

        bool operator!=(const iterator&);
    private:
        T **curr;
        T **end;
        T **begin;

        iterator(T**, T**, T**);


    };

    static_array();

    static_array(size_t );

    size_t current_size();

    static_array(static_array&&);
    static_array(const static_array &);
    ~static_array();

    static_array &operator=(static_array&&);
    static_array &operator=(const static_array &);

    void clear();
    void erase(static_array::iterator);

    size_t size();
    static_array::iterator emplace(size_t , T&&);
    template <class... Args>
    static_array::iterator emplace(size_t , Args&&...);


    T &at(size_t );

    static_array::iterator begin();
    static_array::iterator end();






private:
    T **data;
    size_t curSize;
    size_t count;
};

#endif //HOMEWORK_2_STATIC_ARRAY_H