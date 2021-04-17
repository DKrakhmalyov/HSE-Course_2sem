#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H

#include <cstddef>
#include <vector>
#include <memory>

template<typename T, size_t capacity = 0>
class static_array {
private:
    class element {
    public:
        element();

        element(std::unique_ptr<T> &&oth);

        void replace(T *obj);

        void clear();

        T &get();

        bool valid();

    private:
        std::unique_ptr<T> pointer;
    };

    size_t _current_size = 0;
    size_t _size;
    std::unique_ptr<std::vector<element>> array{};
public:
    class iterator {
    public:
        iterator(const iterator &) = default;

        ~iterator() = default;

        iterator &operator=(const iterator &) = default;

        iterator &operator++();

        iterator &operator--();

        T *operator->() const;

        T &operator*() const;

        bool operator==(const iterator &oth);

        bool operator!=(const iterator &oth);

        iterator(typename std::vector<element>::iterator _it, size_t _pos, size_t size);

        void clear_value();

    private:
        size_t pos;
        size_t _size;
        typename std::vector<element>::iterator it;
    };

    static_array();

    static_array(size_t sz);

    size_t current_size();

    size_t size();

    void clear();

    static_array::iterator emplace(size_t ind, T &&obj);

    template<class... Args>
    static_array::iterator emplace(size_t ind, Args &&... args);

    void erase(static_array::iterator it);

    T &at(size_t ind);

    static_array::iterator begin();

    static_array::iterator end();
};

#endif //HOMEWORK_2_STATIC_ARRAY_H
