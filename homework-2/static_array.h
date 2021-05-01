#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H
#include <vector>
#include <cstddef>

template<typename T, size_t sz = 0>
class static_array {
public:
    class iterator {
    public:
        iterator(const iterator &);

        iterator(static_array<T, sz>* array, size_t ind);

        ~iterator() = default;

        iterator &operator=(const iterator &);

        iterator &operator++();

        iterator &operator--();

        T *operator->() const;

        T &operator*() const;

        friend bool operator==(const iterator &a, const iterator &b){
            return (a.it_index == b.it_index) && (a.master == b.master);
        }

        friend bool operator!=(const iterator &a, const iterator &b){
            return !(a == b);
        }

        static_array* master;

        size_t it_index;
    };

    static_array();

    static_array(size_t size);

    ~static_array();

    size_t current_size() const;

    size_t size() const;

    void clear();

    static_array::iterator emplace(size_t ind, T &&obj);

    template<class... Args>
    static_array::iterator emplace(size_t ind, Args &&... args);

    void erase(static_array::iterator);

    T &at(size_t ind);

    static_array::iterator begin();

    static_array::iterator end();

private:
    T* array;
    std::vector <bool> elem_exists;
    size_t a_capacity;
    size_t a_size;
};

#endif //HOMEWORK_2_STATIC_ARRAY_H
