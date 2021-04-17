#include <stdexcept>

template<typename T, size_t sz = 0>
class static_array {
public:
    class iterator {
    public:

        friend class static_array;

    public:
        iterator(const iterator &);
        ~iterator();

        iterator &operator=(const iterator &);

        iterator &operator++();
        iterator &operator--();

        T *operator->();
        T &operator*();

        bool operator == (const iterator &);
        bool operator != (const iterator &);

    private:

        T** begin;
        T** end;

        T** currentIterator;

        iterator(T** currentIterator, T** begin, T** end);
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

    void erase(static_array::iterator it);

    T& at(size_t ind);

    static_array::iterator begin();
    static_array::iterator end();

private:

    T** dataArray;

    size_t dataArraySize;
    size_t initializedSize;

    bool isValueInitilized(const size_t& pos);
};