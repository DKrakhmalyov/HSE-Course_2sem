#include "static_array.h"

template<typename T, size_t sz>
static_array<T,sz>::iterator::iterator(const iterator &other){
    owner = other.owner;
    pos = other.pos;
}

template<typename T, size_t sz>
static_array<T,sz>::iterator::iterator(static_array<T,sz>* _owner, size_t _pos): owner(_owner), pos(_pos){}

template<typename T, size_t sz>
static_array<T,sz>::iterator::~iterator() = default;

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator=(const static_array::iterator & other){
    if(other == this) {
        return *this;
    }
    owner = other.owner;
    pos = other.pos;
}
template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator++() {
    if(pos >= owner->_size){
        throw std::runtime_error("Error indexing array");
    }
    pos++;
    while(pos < owner->_size && !owner->initialized[pos])
        pos++;
    return *this;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator--() {
    if(pos <= 0){
        throw std::runtime_error("Error indexing array");
    }
    pos--;
    while(pos > 0 && !owner->initialized[pos])
        pos--;
    return *this;
}

template<typename T, size_t sz>
T* static_array<T, sz>::iterator::operator->() const{
    if(pos < 0 || pos >= owner->_size){
        throw std::runtime_error("Error indexing array");
    }
    if(!owner->initialized[pos]){
        throw std::runtime_error("There is no available data");
    }
    return (owner->data[pos]);
}

template<typename T, size_t sz>
T& static_array<T, sz>::iterator::operator*() const{
    if(pos < 0 || pos >= owner->_size){
        throw std::runtime_error("Error indexing array");
    }
    if(!owner->initialized[pos]){
        throw std::runtime_error("There is no available data");
    }
    return *(owner->data[pos]);
}

template <typename T, size_t sz>
bool static_array<T, sz>::iterator::operator==(
        typename static_array<T, sz>::iterator const &other) const {
    return (owner == other.owner) && (pos == other.pos);
}

template <typename T, size_t sz>
bool static_array<T, sz>::iterator::operator!=(
        typename static_array<T, sz>::iterator const &other) const {
    return (!((*this) == other));
}

template<typename T, size_t sz>
static_array<T, sz>::static_array(): static_array(sz) {}

template<typename T, size_t sz>
static_array<T, sz>::static_array(size_t max_size):_size(max_size), _current_size(0){
    initialized = std::vector<bool>(max_size);
    data = std::vector<T*>(max_size);
}

template<typename T, size_t sz>
size_t static_array<T, sz>::current_size() {
    return _current_size;
}

template<typename T, size_t sz>
size_t static_array<T, sz>::size() {
    return _size;
}

template<typename T, size_t sz>
void static_array<T, sz>::clear(){
    for(auto it = begin(); it != end(); ++it){
        erase(it);
    }
}

template<typename T, size_t sz>
typename static_array<T,sz>::iterator static_array<T,sz>::emplace(size_t ind, T &&obj){

    if(initialized[ind]){
        erase(iterator(this, ind));
    }
    data[ind] = new T(std::forward<T>(obj));
    initialized[ind] = true;
    _current_size++;

    return static_array::iterator(this, ind);
}

template <typename T, size_t sz>
template <class... Args>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(
        size_t ind, Args &&...args) {
    if(initialized[ind]){
        erase(iterator(this, ind));
    }
    data[ind] = new T(std::forward<Args>(args)...);
    initialized[ind] = true;
    _current_size++;
    return static_array::iterator(this, ind);
}

template<typename T, size_t sz>
void static_array<T, sz>::erase(static_array::iterator it){
    if(it.pos < 0 || it.pos >= _size){
        throw std::runtime_error("Error indexing array");
    }
    if(!initialized[it.pos])
        return;
    initialized[it.pos] = false;
    --_current_size;
    delete data[it.pos];
}


template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::begin() {
    return iterator(this, 0);
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::end() {
    return iterator(this, _size);
}

template<typename T, size_t sz>
T& static_array<T,sz>::at(size_t ind){
    if(ind < 0 || ind >= _size){
        throw std::runtime_error("Error indexing array");
    }
    if(!initialized[ind]){
        throw std::runtime_error("not initialized");
    }
    return *data[ind];
}