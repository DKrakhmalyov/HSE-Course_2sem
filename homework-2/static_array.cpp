#include "static_array.h"

template<typename T, size_t capacity>
static_array<T, capacity>::static_array():
    array(std::make_unique<std::vector<element>>(capacity)), _current_size(0), _size(capacity) {}

template<typename T, size_t capacity>
static_array<T, capacity>::static_array(size_t size):
    array(std::make_unique<std::vector<element>>(size)), _current_size(0), _size(size) {}

template<typename T, size_t capacity>
size_t static_array<T, capacity>::current_size() {
    return _current_size;
}

template<typename T, size_t capacity>
size_t static_array<T, capacity>::size() {
    return array->size();
}

template<typename T, size_t capacity>
void static_array<T, capacity>::clear() {
    _current_size = 0;
    for (int i = 0; i < _size; i++) {
        array->at(i).clear();
    }
}

template<typename T, size_t capacity>
typename static_array<T, capacity>::iterator static_array<T, capacity>::emplace(size_t ind, T &&obj) {
    if (!array->at(ind).valid()) {
        _current_size++;
    }
    array->at(ind).replace(new T(std::move(obj)));
    return typename static_array<T, capacity>::iterator(array->begin() + ind, ind, _size);
}

template<typename T, size_t capacity>
template<class... Args>
typename static_array<T, capacity>::iterator static_array<T, capacity>::emplace(size_t ind, Args &&... args) {
    if (!array->at(ind).valid()) {
        _current_size++;
    }
    array->at(ind).replace(new T(std::forward<Args>(args)...));
    return typename static_array<T, capacity>::iterator(array->begin() + ind, ind, _size);
}

template<typename T, size_t capacity>
void static_array<T, capacity>::erase(static_array::iterator it) {
    _current_size--;
    it.clear_value();
}

template<typename T, size_t capacity>
T &static_array<T, capacity>::at(size_t ind) {
    array->at(ind).get();
}

template<typename T, size_t capacity>
typename static_array<T, capacity>::iterator static_array<T, capacity>::begin() {
    auto it = array->begin();
    while (it != array->end()) {
        if (it->valid()) {
            break;
        }
        it++;
    }
    return typename static_array<T, capacity>::iterator(it, it - array->begin(), _size);
}

template<typename T, size_t capacity>
typename static_array<T, capacity>::iterator static_array<T, capacity>::end() {
    return typename static_array<T, capacity>::iterator(array->end(), _size, _size);
}

template<typename T, size_t capacity>
static_array<T, capacity>::element::element() : pointer(nullptr) { }

template<typename T, size_t capacity>
void static_array<T, capacity>::element::replace(T *obj) {
    pointer.reset(obj);
}

template<typename T, size_t capacity>
void static_array<T, capacity>::element::clear() {
    pointer.reset(nullptr);
}

template<typename T, size_t capacity>
T &static_array<T, capacity>::element::get() {
    return *pointer.get();
}

template<typename T, size_t capacity>
bool static_array<T, capacity>::element::valid() {
    return pointer.get() != nullptr;
}

template<typename T, size_t capacity>
static_array<T, capacity>::element::element(std::unique_ptr<T> &&oth) : pointer(oth) { }

template<typename T, size_t capacity>
static_array<T, capacity>::iterator::iterator(typename std::vector<static_array::element>::iterator _it, size_t _pos, size_t size) :
    it(_it), pos(_pos), _size(size) { }

template<typename T, size_t capacity>
typename static_array<T, capacity>::iterator &static_array<T, capacity>::iterator::operator++() {
    do {
        it++;
        pos++;
    } while(pos < _size && !it->valid());
    return *this;
}

template<typename T, size_t capacity>
typename static_array<T, capacity>::iterator &static_array<T, capacity>::iterator::operator--() {
    do {
        it--;
        pos--;
    } while(!it->valid());
    return *this;
}

template<typename T, size_t capacity>
T *static_array<T, capacity>::iterator::operator->() const {
    return &it->get();
}

template<typename T, size_t capacity>
T &static_array<T, capacity>::iterator::operator*() const {
    return it->get();
}

template<typename T, size_t capacity>
void static_array<T, capacity>::iterator::clear_value() {
    it->clear();
    ++(*this);
}

template<typename t, size_t capacity>
bool static_array<t, capacity>::iterator::operator==(const static_array::iterator &oth) {
    return this->it == oth.it;
}

template<typename t, size_t capacity>
bool static_array<t, capacity>::iterator::operator!=(const static_array::iterator &oth) {
    return this->it != oth.it;
}

