//
// Created by Denis on 12.03.2021.
//

// #include <stdexcept>
// #include <memory>
// #include <vector>

// #include "static_array.h"


// template<typename T, size_t sz>
// static_array<T, sz>::static_array() : static_array(sz) { };

// template<typename T, size_t sz>
// static_array<T, sz>::static_array(size_t copacity) : _copacity(copacity) {
//   _data = new char[copacity * sizeof(T)];
//   _initialized.resize(copacity);
// };

// template<typename T, size_t sz>
// size_t static_array<T, sz>::current_size() {
//   return _current_size;
// };

// template<typename T, size_t sz>
// size_t static_array<T, sz>::size() {
//   return _copacity;
// };

// template<typename T, size_t sz>
// void static_array<T, sz>::clear() {
//   for (auto i = begin(); i != end(); ++i)
//     erase(i);
// };

// template<typename T, size_t sz>
// static_array::iterator static_array<T, sz>::emplace(size_t ind, T &&obj) {
//   _check_bounds(ind);
//   if (_initialized[ind]) {
//     reinterpret_cast<T*>(_data + sizeof(T)*ind)->~T();
//     --_current_size;
//   }
//   new (_data + sizeof(T)*ind) T(std::forward<T>(obj));
//   _initialized[ind] = true;
//   ++_current_size;
//   return static_array::iterator(ind);
// };

// template<typename T, size_t sz, class... Args>
// static_array::iterator static_array<T, sz>::emplace(size_t ind, Args &&... args) {
//   check_bounds_(ind);
//   if (_initialized[ind]) {
//     reinterpret_cast<T*>(_data + sizeof(T)*ind)->~T();
//     --_current_size;
//   }
//   new (_data + sizeof(T)*ind) T(std::forward<Args>(args)...);
//   _initialized[ind] = true;
//   ++_current_size;
// };

// template<typename T, size_t sz>
// void static_array<T, sz>::erase(static_array::iterator) {

// };

// template<typename T, size_t sz>
// T& static_array<T, sz>::at(size_t ind) {
//   _check_bounds(ind);
//   _check_is_initialized(ind);
//   return *reinterpret_cast<T*>(_data + sizeof(T) * ind);
// };

// template<typename T, size_t sz>
// static_array::iterator static_array<T, sz>::begin() {
//   return static_array::iterator(
//       reinterpret_cast<T*>(_data + sizeof(T) * _get_mext_avaliable_index(-1))
//     );
// };

// template<typename T, size_t sz>
// static_array::iterator static_array<T, sz>::end() {
//   return static_array::iterator(reinterpret_cast<T*>(_data + sizeof(T) * _copacity));
// };


// template<typename T, size_t sz>
// void static_array<T, sz>::_check_bounds(size_t& ind) {
//   if (ind >= _copacity)
//     throw std::out_of_range("static_array: Index out of range");
// };

// template<typename T, size_t sz>
// void static_array<T, sz>::_check_is_initialized(size_t& ind) {
//   if (!_initialized[ind])
//     throw std::runtime_error("static_array: Value is not initialized");
// }

// template<typename T, size_t sz>
// size_t static_array<T, sz>::_get_mext_avaliable_index(size_t index) {
//   for (++index; index < _copacity; ++index)
//     if (_initialized[index]) 
//       break;
//   return index;
// }
