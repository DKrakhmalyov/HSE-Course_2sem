#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H

#include <cstddef>
#include <cstdint>
#include <vector>

template<typename T, size_t sz = 0>
class static_array {
public:
    class iterator {
    public:
        size_t pos;
        static_array<T,sz>* owner;

        iterator(static_array<T,sz>*, size_t);
        iterator(const iterator &);

        ~iterator();

        iterator &operator=(const iterator &);

        iterator &operator++();

        iterator &operator--();

        T *operator->() const;

        T &operator*() const;

        bool operator==(const iterator &) const;

        bool operator!=(const iterator &) const;
    };

    static_array();

    static_array(size_t max_size);

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
    size_t _size = sz;
    size_t _current_size = 0;
    std::vector<bool> initialized;
    std::vector<T *> data;




};

#endif //HOMEWORK_2_STATIC_ARRAY_H
