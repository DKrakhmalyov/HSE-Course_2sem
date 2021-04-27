#include "static_array.h"

template <typename T, std::size_t sz>
static_array<T, sz>::iterator::iterator(const static_array<T, sz>::iterator& it) {
    self_iter = it.self_iter;
}

template <typename T, std::size_t sz>
static_array<T, sz>::iterator::~iterator() {
    self_iter = nullptr;
}

template <typename T, std::size_t sz>
typename static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator=(
    const static_array<T, sz>::iterator &other
) {
    if (this != &other) {
        self_iter = other.self_iter;
    }
    return *this;
 }

template <typename T, std::size_t sz>
typename static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator++() {
    bool first_step_flag = true;
    while ((self_iter != arr->array + arr->size()) && ((*self_iter == nullptr) || first_step_flag)) {
        ++self_iter;
        first_step_flag = false;
    }
    return *this;
}   

template <typename T, std::size_t sz>
typename static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator--() {
    bool first_step_flag = true;
    while ((self_iter != arr->array) && ((*self_iter == nullptr) || first_step_flag)) {
        --self_iter;
        first_step_flag = false;
    }
    return *this;
}

template <typename T, std::size_t sz>
T* static_array<T, sz>::iterator::operator->() {
    return *this->self_iter;
}

template<typename T, std::size_t sz>
T& static_array<T, sz>::iterator::operator*() {
    return **this->self_iter;
}

template <typename T, std::size_t sz >
bool static_array<T, sz>::iterator::operator==(
    const static_array<T, sz>::iterator &other
) {
    return self_iter == other.self_iter;
}

template <typename T, std::size_t sz>
bool static_array<T, sz>::iterator::operator!=(
    const static_array<T, sz>::iterator &other
) {
    return !operator==(other);
}

template <typename T, std::size_t sz>
static_array<T, sz>::iterator::iterator(T** _self_iter, static_array<T, sz>* _arr) :
    self_iter(_self_iter),
    arr(_arr)
{}

template <typename T, std::size_t sz>
static_array<T, sz>::static_array() {
    total_count = sz;
    elements_count = 0;
    init_array();
}

template <typename T, std::size_t sz>
static_array<T, sz>::static_array(std::size_t size) {
    total_count = std::max(size, sz);
    elements_count = 0;
    init_array();
}

template <typename T, std::size_t sz>
static_array<T, sz>::~static_array() {
    clear();
}

template<typename T, std::size_t sz>
void static_array<T, sz>::static_array::clear() {
    delete_elements();
    delete[] array;
    array = nullptr;
    total_count = 0;
}

template <typename T, std::size_t sz>
static_array<T, sz>::iterator static_array<T, sz>::static_array::emplace(size_t pos, T &&obj) {
    if (*(array + pos) == nullptr) {
        elements_count++;
    } else {
        delete array[pos];
    }
    array[pos] = new T(std::forward<T>(obj));
    return create_iter(pos);
}

template <typename T, std::size_t sz>
template<class... Args>
static_array<T, sz>::iterator static_array<T, sz>::static_array::emplace(size_t pos, Args &&... args) {
    if (*(array + pos) == nullptr) {
        elements_count++;
    } else {
        delete array[pos];
    }
    array[pos] = new T(std::forward<Args>(args)...);
    return create_iter(pos);
}

template <typename T, std::size_t sz>
void static_array<T, sz>::static_array::erase(static_array<T, sz>::iterator iter) {
    if (*iter.self_iter != nullptr) {
        delete *iter.self_iter;
        --elements_count;
        *iter.self_iter = nullptr;
    }
}

template <typename T, std::size_t sz>
T& static_array<T, sz>::static_array::at(std::size_t pos) {
    if (pos >= total_count) {
        throw std::out_of_range(
            "You tried to use element on position " + std::to_string(pos) + 
            " but there is only " + std::to_string(total_count) +
            " elements in array"
        );
    }
    if (array[pos] == nullptr) {
        throw std::invalid_argument(
            "You tried to use non-existent element"
        );
    }
    return *array[pos];
}

template <typename T, std::size_t sz>
std::size_t static_array<T, sz>::static_array::current_size() const {
    return elements_count;
}

template <typename T, std::size_t sz>
std::size_t static_array<T, sz>::static_array::size() const {
    return total_count;
}

template <typename T, std::size_t sz>
static_array<T, sz>::iterator static_array<T, sz>::static_array::begin() {
    return create_iter(0);
}

template <typename T, std::size_t sz>
static_array<T, sz>::iterator static_array<T, sz>::static_array::end() {
    return create_iter(total_count);
}

template <typename T, std::size_t sz>
void static_array<T, sz>::static_array::init_array() {
    array = new T*[total_count + 1];
    for (std::size_t pos = 0; pos < total_count; ++pos) {
        array[pos] = nullptr;
    }
}

template <typename T, std::size_t sz>
void static_array<T, sz>::static_array::delete_elements() {
    for (std::size_t pos = 0; pos < total_count; ++pos) {
        if (*(array + pos) != nullptr) {
            delete array[pos];
            --elements_count;
            array[pos] = nullptr;
        }
    }
}

template <typename T, std::size_t sz>
static_array<T, sz>::iterator static_array<T, sz>::static_array::create_iter(std::size_t pos) {
    return static_array<T, sz>::iterator(array + pos, this);
}
