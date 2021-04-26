#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H

#include <cstddef>
#include <vector>
#include <optional>

template<typename T, size_t sz = 0>
class static_array {
    using storage = std::vector<std::optional<T>>;

    storage arr;
    const size_t size_;
    size_t current_size_{0};

public:
    class iterator {
        static_array* container;
        size_t index;

        iterator(static_array *container, size_t index);

    public:
        iterator(const iterator &);

        ~iterator() = default;

        iterator &operator=(const iterator &);

        iterator &operator++();

        iterator &operator--();

        T *operator->() const;

        T &operator*() const;

        bool operator==(const iterator &oth);

        bool operator!=(const iterator &oth);

        friend class static_array;
    };

    static_array();

    static_array(size_t size);

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
