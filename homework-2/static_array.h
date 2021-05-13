//
// Created by Denis on 12.03.2021.
//

#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H

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

        friend bool operator==(const iterator &, const iterator &);

        friend bool operator!=(const iterator &, const iterator &);
    };

    static_array();

    static_array(size_t sz);

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

#endif //HOMEWORK_2_STATIC_ARRAY_H
