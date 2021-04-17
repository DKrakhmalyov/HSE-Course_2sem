#include "static_array.h"

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator(T** currentIterator, T** begin, T** end) {
    this->currentIterator = currentIterator;
    this->begin = begin;
    this->end = end;
}

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator(const static_array<T, sz>::iterator& it) {
    this->currentIterator = it.currentIterator;
    this->begin = it.begin;
    this->end = it.end;
}

template<typename T, size_t sz>
static_array<T, sz>::iterator::~iterator() {

}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator=(const static_array<T, sz>::iterator &it) {
    this->currentIterator = new T**(it.currentIterator);
    this->begin = new T(it.begin);
    this->end = new T(it.end);
    return *this;
 }

template<typename T, size_t sz >
typename static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator++() {
    if (this->currentIterator != this->end) {
        this->currentIterator++;
    }
    while (this->currentIterator != this->end && !*this->currentIterator) {
        ++this->currentIterator;
    }
    return *this;
}

template<typename T, size_t sz >
typename static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator--() {
    if (this->currentIterator != this->begin) {
        --this->currentIterator;
    }
    while (this->currentIterator != this->begin && !*this->currentIterator) {
        --this->currentIterator;
    }
    return *this;
}

template<typename T, size_t sz >
T *static_array<T, sz>::iterator::operator->() {
    return *this->currentIterator;
}

template<typename T, size_t sz >
T &static_array<T, sz>::iterator::operator*() {
    return **this->currentIterator;
}

template<typename T, size_t sz >
bool static_array<T, sz>::iterator::operator == (const static_array<T, sz>::iterator &it) {
    return this->currentIterator == it.currentIterator;
}

template<typename T, size_t sz>
bool static_array<T, sz>::iterator::operator != (const static_array<T, sz>::iterator &it) {
    return this->currentIterator != it.currentIterator;
}

template<typename T, size_t sz>
static_array<T, sz>::static_array() {
    dataArray = new T*[sz + 1];
    dataArraySize = sz;
    initializedSize = 0;
    for (size_t i = 0; i < sz; i++) {
        dataArray[i] = nullptr;
    }
}

template<typename T, size_t sz>
static_array<T, sz>::static_array(size_t size) {
    if (size < sz) {
        size = sz;
    }
    dataArray = new T*[size + 1];
    dataArraySize = size;
    initializedSize = 0;
    for (size_t i = 0; i < size; i++) {
        dataArray[i] = nullptr;
    }
}

template<typename T, size_t sz>
size_t static_array<T, sz>::current_size() {
    return initializedSize;
}

template<typename T, size_t sz>
size_t static_array<T, sz>::size() {
    return dataArraySize;
}

template<typename T, size_t sz>
void static_array<T, sz>::clear(){
    const size_t& size = dataArraySize;
    for (size_t i = 0; i < size; i++) {
        if (dataArray[i] == nullptr) {
            continue;
        }
        delete dataArray[i];
        dataArray[i] = nullptr;
    }
    delete[] dataArray;
    dataArray = nullptr;
    dataArraySize = 0;
    initializedSize = 0;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, T&& obj) {
    if (!isValueInitilized(ind)) {
        initializedSize++;
    }
    dataArray[ind] = new T(std::forward<T>(obj));
    return static_array<T, sz>::iterator(
        dataArray + ind,
        dataArray,
        dataArray + dataArraySize
    );
}

template<typename T, size_t sz>
template<class... Args>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, Args &&... args) {
    if (!isValueInitilized(ind)) {
        initializedSize++;
    }
    dataArray[ind] = new T(std::forward<Args>(args)...);
    return static_array<T, sz>::iterator(
        dataArray + ind,
        dataArray,
        dataArray + dataArraySize
    );
}

template<typename T, size_t sz>
void static_array<T, sz>::erase(static_array<T, sz>::iterator it) {
    delete *it.currentIterator;
    *it.currentIterator = nullptr;
    initializedSize -= 1;
}

template<typename T, size_t sz>
T& static_array<T, sz>::at(size_t ind) {
    if (ind >= dataArraySize) {
        throw std::out_of_range("Invalid index: " + ind);
    }
    if (!isValueInitilized(ind)) {
        throw std::invalid_argument("Value is not Initilized!");
    }
    return *dataArray[ind];
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::begin() {
    return static_array<T, sz>::iterator(
        dataArray, 
        dataArray, 
        dataArray + dataArraySize
    );
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::end() {
    return static_array<T, sz>::iterator(
        dataArray + dataArraySize, 
        dataArray, 
        dataArray + dataArraySize
    );
}

template<typename T, size_t sz>
static_array<T, sz>::~static_array() {
    clear();
}

template<typename T, size_t sz>
bool static_array<T, sz>::isValueInitilized(const size_t& pos) {
    if (dataArray[pos] == nullptr) {
        return false;
    }
    return true;
}