//
// Created by Denis on 12.03.2021.
//

#include "static_array.h"

#include <utility>

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator(T** ptr, size_t index, size_t size) : ptr(ptr), index(index), size(size) {}

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator(const iterator &other) : ptr(other.ptr), index(other.index), size(other.size) {}

template<typename T, size_t sz>
static_array<T, sz>::iterator::~iterator() {}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator=(const iterator &other) {
	ptr = other.ptr;
	return *this;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator++() {
	size_t end = size;
	for (size_t i = size - index - 1; i >= 0; --i) {
		if (*(ptr + i) != nullptr) {
			end = index + i + 1;
			break;
		}
	}
	do {
		ptr++;
		index++;
	} while (index < end && *ptr == nullptr);
	return *this;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator--() {
	size_t begin = 0;
	for (size_t i = index; i >= 0; --i) {
		if (*(ptr - i) != nullptr) {
			begin = index - i;
			break;
		}
	}
	do {
		ptr--;
		index--;
	} while (index > begin && *ptr == nullptr);
	return *this;
}

template<typename T, size_t sz>
T *static_array<T, sz>::iterator::operator->() const {
	return *ptr;
}

template<typename T, size_t sz>
T &static_array<T, sz>::iterator::operator*() const {
	return **ptr;
}

template<class T, size_t sz>
bool static_array<T, sz>::iterator::operator==(static_array<T, sz>::iterator const& other) const {
	return ptr == other.ptr;
}

template<class T, size_t sz>
bool static_array<T, sz>::iterator::operator!=(static_array<T, sz>::iterator const& other) const {
	return ptr != other.ptr;
}

template<typename T, size_t sz>
static_array<T, sz>::static_array() : _size(sz), _curr_size(0), arr(new T*[sz + 1]) {
	for (size_t i = 0; i <= sz; ++i) {
		arr[i] = nullptr;
	}
}

template<typename T, size_t sz>
static_array<T, sz>::static_array(size_t size) : _size(size), _curr_size(0), arr(new T*[size + 1]) {
	for (size_t i = 0; i <= size; ++i) {
		arr[i] = nullptr;
	}
}

template<typename T, size_t sz>
static_array<T, sz>::~static_array() {
	for (size_t i = 0; i < _size; ++i) {
		if (arr[i] != nullptr)
			delete arr[i];
	}
	delete[] arr;
}

template<typename T, size_t sz>
size_t static_array<T, sz>::current_size() {
	return _curr_size;
}

template<typename T, size_t sz>
size_t static_array<T, sz>::size() {
	return _size;
}

template<typename T, size_t sz>
void static_array<T, sz>::clear() {
	for (size_t i = 0; i < _size; ++i) {
		if (arr[i] != nullptr) {
			delete arr[i];
			arr[i] = nullptr;
		}
	}
	_curr_size = 0;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, T &&obj) {
	if (arr[ind] != nullptr) {
		delete arr[ind];
		_curr_size--;
	}
	_curr_size++;
	arr[ind] = new T(std::forward<T>(obj));
	return static_array::iterator(arr + ind, ind, _size);
}

template<typename T, size_t sz>
template<class... Args>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, Args &&... args) {
	if (arr[ind] != nullptr) {
		delete arr[ind];
		_curr_size--;
	}
	_curr_size++;
	arr[ind] = new T(std::forward<Args>(args)...);
	return static_array::iterator(arr + ind, ind, _size);
}

template<typename T, size_t sz>
void static_array<T, sz>::erase(static_array::iterator it) {
	if (*it.ptr == nullptr)
		return;
	delete *it.ptr;
	*it.ptr = nullptr;
	_curr_size--;
}

template<typename T, size_t sz>
T& static_array<T, sz>::at(size_t ind) {
	if (arr[ind] != nullptr)
		return *arr[ind];
	if (ind >= 0 || ind < sz) {
		throw("Object is not initialized");
	} else {
		throw("Index is out of range");
	}
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::begin() {
	for (size_t i = 0; i < _size; ++i) {
		if (arr[i] != nullptr)
			return iterator(arr + i, i, _size);
	}
	return iterator(arr, 0, _size);
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::end() {
	for (size_t i = _size - 1; i >= 0; --i) {
		if (arr[i] != nullptr)
			return iterator(arr + i + 1, i + 1, _size);
	}
	return iterator(arr, 0, _size);
}
