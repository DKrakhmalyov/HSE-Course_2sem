//
// Created by Denis on 12.03.2021.
//

#ifndef STATIC_ARRAY_CPP
#define STATIC_ARRAY_CPP

#include "static_array.h"

#include <stdexcept>

namespace detail {

template <typename T>
inline T& GetByIndex(uint8_t* memory, size_t index) {
  return *reinterpret_cast<T*>(memory + sizeof(T) * index);
}

template <typename T>
inline void CreateAtIndex(uint8_t* memory, size_t index, T&& object) {
  void* pointer = memory + sizeof(T) * index;
  new (pointer) T(std::forward<T>(object));
}

template <typename T, typename... Args>
inline void CreateAtIndex(uint8_t* memory, size_t index, Args&&... args) {
  void* pointer = memory + sizeof(T) * index;
  new (pointer) T(std::forward<Args>(args)...);
}

}  // namespace detail
template <typename T, size_t capacity>
inline size_t static_array<T, capacity>::current_size() const {
  return m_size;
}

template <typename T, size_t capacity>
inline size_t static_array<T, capacity>::size() const {
  return m_capacity;
}

template <typename T, size_t capacity>
inline void static_array<T, capacity>::clear() {
  for (size_t i = 0; i < m_size; ++i) {
    if (m_has_value[i]) {
      detail::GetByIndex<T>(m_data, i).~T();
    }
  }
  std::fill(m_has_value.begin(), m_has_value.end(), false);
  m_size = 0;
}

template <typename T, size_t capacity>
template <typename... Args>
inline typename static_array<T, capacity>::iterator
static_array<T, capacity>::emplace(size_t index, Args&&... args) {
  if (m_has_value[index]) {
    detail::GetByIndex<T>(m_data, index).~T();
  } else {
    m_size++;
    m_has_value[index] = true;
  }
  detail::CreateAtIndex<T>(m_data, index, std::forward<Args>(args)...);
  return iterator(this, index);
}

template <typename T, size_t capacity>
inline typename static_array<T, capacity>::iterator
static_array<T, capacity>::emplace(size_t index, T&& element) {
  if (m_has_value[index]) {
    detail::GetByIndex<T>(m_data, index).~T();
  } else {
    m_size++;
    m_has_value[index] = true;
  }
  detail::CreateAtIndex<T>(m_data, index, std::forward<T>(element));
  return iterator(this, index);
}

template <typename T, size_t capacity>
inline T& static_array<T, capacity>::at(size_t index) {
  if (index >= m_capacity) {
    throw std::out_of_range("Index is too large");
  }
  if (!m_has_value[index]) {
    throw std::runtime_error("Value is unset");
  }
  return detail::GetByIndex<T>(m_data, index);
}

template <typename T, size_t capacity>
inline static_array<T, capacity>::iterator::iterator(const iterator& other)
    : m_container(other.m_container), m_index(other.m_index) {}

template <typename T, size_t capacity>
inline static_array<T, capacity>::iterator::~iterator() = default;

template <typename T, size_t capacity>
inline typename static_array<T, capacity>::iterator&
static_array<T, capacity>::iterator::operator=(const iterator& other) {
  m_container = other.m_container;
  m_index = other.m_index;
}

template <typename T, size_t capacity>
inline typename static_array<T, capacity>::iterator&
static_array<T, capacity>::iterator::operator++() {
  m_index = iterator::GetNextInitialized(m_container, m_index + 1);
  return *this;
}

template <typename T, size_t capacity>
inline typename static_array<T, capacity>::iterator&
static_array<T, capacity>::iterator::operator--() {
  m_index = GetPreviousInitialized(m_container, m_index - 1);
  return *this;
}

template <typename T, size_t capacity>
inline T* static_array<T, capacity>::iterator::operator->() const {
  return &detail::GetByIndex<T>(m_container->m_data, m_index);
}

template <typename T, size_t capacity>
inline T& static_array<T, capacity>::iterator::operator*() const {
  return detail::GetByIndex<T>(m_container->m_data, m_index);
}

template <typename T, size_t capacity>
inline static_array<T, capacity>::iterator::iterator(
    static_array<T, capacity>* container, size_t index)
    : m_container(container), m_index(index) {}

template <typename T, size_t capacity>
inline void static_array<T, capacity>::erase(static_array::iterator iterator) {
  m_has_value[iterator.m_index] = false;
  detail::GetByIndex<T>(m_data, iterator.m_index).~T();
  m_size--;
}

template <typename T, size_t capacity>
inline typename static_array<T, capacity>::iterator
static_array<T, capacity>::begin() {
  return iterator(this, iterator::GetNextInitialized(this, 0));
}

template <typename T, size_t capacity>
inline typename static_array<T, capacity>::iterator
static_array<T, capacity>::end() {
  return iterator(this, m_capacity);
}

template <typename T, size_t capacity>
inline bool static_array<T, capacity>::iterator::operator==(const typename static_array<T, capacity>::iterator& other) const {
  return m_container == other.m_container && m_index == other.m_index;
}

template <typename T, size_t capacity>
inline bool static_array<T, capacity>::iterator::operator!=(typename static_array<T, capacity>::iterator const& other) const {
  return !(*this == other);
}

template <typename T, size_t capacity>
inline size_t static_array<T, capacity>::iterator::GetNextInitialized(
    const static_array<T, capacity>* container,
    size_t starting_index) {
  for (size_t pos = starting_index; pos < container->m_capacity; ++pos) {
    if (container->m_has_value[pos]) {
      return pos;
    }
  }
  return container->m_capacity;
}

template <typename T, size_t capacity>
inline size_t static_array<T, capacity>::iterator::GetPreviousInitialized(
    const static_array<T, capacity>* container,
    size_t starting_index) {
  for (size_t pos = starting_index; pos < std::numeric_limits<size_t>::max(); --pos) {
    if (container->m_has_value[pos]) {
      return pos;
    }
  }
  return container->m_capacity;
}

template <typename T, size_t capacity>
inline static_array<T, capacity>::~static_array() {
  clear();
  delete[] m_data;
}

#endif  // STATIC_ARRAY_CPP
