#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H

#include <utility>
#include <cstddef>
#include <algorithm>
#include <stdexcept>

template<typename T, std::size_t sz = 0>
class static_array {
public:
    
    class iterator {
    
    friend class static_array;

    public:

        iterator(const iterator &);

        ~iterator();

        iterator &operator=(const iterator &);

        iterator &operator++();

        iterator &operator--();

        T *operator->() const;

        T &operator*() const;

        bool operator==(const iterator &);

        bool operator!=(const iterator &);

    private:

        iterator(T* data, int *used, bool *initialized);


    public:

        T *m_data_ptr;

        int *m_used_ptr;

        bool *m_initialized_ptr;

    };

    static_array();

    ~static_array();

    static_array(size_t n_sz);

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

public:
    
    T *m_data;

    int *m_used;

    bool *m_initialized;

    size_t m_size = sz;

    size_t m_current_size = 0;

};

#endif //HOMEWORK_2_STATIC_ARRAY_H
