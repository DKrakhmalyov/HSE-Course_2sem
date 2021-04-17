//
// Created by Denis on 12.03.2021.
//

#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H

#include <cstddef>

template<typename T, size_t SZ = 0>
class static_array {
private:
    T *mem_ptr;
    char *mask;
    size_t _sz;
    size_t _true_sz;

    bool get_init(size_t i);

    void set_init(size_t i, bool init);

public:
    class iterator {
        friend class static_array;
    private:
        T *_ptr;
        static_array& _instance;
    public:

        iterator(T *, static_array& instance);
        iterator(const iterator &);

        ~iterator() = default;

        iterator &operator=(const iterator &);

        iterator &operator++();

        iterator &operator--();

        T *operator->() const;

        T &operator*() const;

        friend bool operator==(const iterator &lhs, const iterator &rhs){
            return lhs._ptr == rhs._ptr;
        }

        friend bool operator!=(const iterator &lhs, const iterator &rhs){
            return !(lhs == rhs);
        }
    };

    static_array();

    explicit static_array(size_t sz);

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
};

#include "static_array.cpp"
#endif //HOMEWORK_2_STATIC_ARRAY_H
