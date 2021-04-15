//
// Created by Denis on 12.03.2021.
//

#include <stdexcept>
#include "static_array.h"

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator(const static_array::iterator &o) {
  m_owner = o.m_owner;
  m_pos = o.m_pos;
}

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator(std::size_t pos, static_array<T, sz> *owner): m_pos(pos), m_owner(owner) {}

template<typename T, size_t sz>
static_array<T, sz>::iterator::~iterator() = default;

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator=(const static_array::iterator &o) {
  if (o == this) return *this;

  m_pos = o.m_pos;
  m_owner = o.m_owner;
  return *this;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator++() {
  if (m_pos >= m_owner->m_capacity)
    throw std::range_error("Moving iterator higher than it's end.");

  m_pos++;
  while (m_pos < m_owner->m_capacity && !m_owner->m_init[m_pos]) {
    m_pos++;
  }

  return *this;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator--() {
  if (m_pos <= 0)
    throw std::range_error("Moving iterator lower than it's start.");

  m_pos--;
  while (m_pos > 0 && !m_owner->m_init[m_pos])
    m_pos--;

  return *this;
}

template<typename T, size_t sz>
T *static_array<T, sz>::iterator::operator->() const {
  m_owner->_precond_available(m_pos);
  return m_owner->_int_at(m_pos);
}

template<typename T, size_t sz>
T &static_array<T, sz>::iterator::operator*() const {
  m_owner->_precond_available(m_pos);
  return *m_owner->_int_at(m_pos);
}


template<typename T, size_t sz>
static_array<T, sz>::static_array(): static_array(sz) {}

template<typename T, size_t sz>
static_array<T, sz>::static_array(size_t capacity) : m_capacity(capacity) {
  m_data = new int8_t[capacity * sizeof(T)];
  m_init = std::vector<bool>(capacity);
}

template<typename T, size_t sz>
size_t static_array<T, sz>::current_size() {
  return m_size;
}

template<typename T, size_t sz>
size_t static_array<T, sz>::size() {
  return m_capacity;
}

template<typename T, size_t sz>
void static_array<T, sz>::clear() {
  for (auto it = begin(); it != end(); ++it) {
    erase(it);
  }
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::_int_write(size_t index, T &&value) {
  _precond_index(index);

  // Erase element if it is present.
  if (m_init[index]) {
    erase(iterator(index, this));
  }

  // Write new element to corresponding position.
  *_int_at(index) = std::move(value);

  m_init[index] = true;
  ++m_size;
  return static_array::iterator(index, this);
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t index, T &&obj) {
  return _int_write(index, std::forward<T>(obj));
}

template<typename T, size_t sz>
template<class... Args>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t index, Args &&... args) {
  return _int_write(index, std::move(T(std::forward<Args>(args)...)));
}

template<typename T, size_t sz>
void static_array<T, sz>::erase(static_array::iterator it) {
  _precond_index(it.m_pos);

  if (!m_init[it.m_pos]) return;

  it->~T();
  --m_size;
  m_init[it.m_pos] = false;
}

template<typename T, size_t sz>
T &static_array<T, sz>::at(size_t ind) {
  _precond_available(ind);
  return *_int_at(ind);
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::begin() {
  return iterator(0, this);
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::end() {
  return iterator(m_capacity, this);
}

template<typename T, size_t sz>
T *static_array<T, sz>::_int_at(size_t index) const {
  return reinterpret_cast<T *>(m_data) + index;
}

template<typename T, size_t sz>
void static_array<T, sz>::_precond_index(std::size_t index) const {
  if (!(0 <= index && index < m_capacity)) {
    throw std::range_error("Error indexing array with index '" + std::to_string(index) + "'");
  }
}

template<typename T, size_t sz>
void static_array<T, sz>::_precond_available(std::size_t index) const {
  _precond_index(index);

  if (!m_init[index]) {
    throw std::range_error("Error accessing index '" + std::to_string(index) + "': no available data.");
  }
}

template<typename T, size_t sz>
static_array<T, sz>::~static_array() {
  clear();
  delete[] m_data;
}

template<typename T, size_t sz>
bool static_array<T, sz>::iterator::operator==(const static_array::iterator &rhs) {
  return m_pos == rhs.m_pos && m_owner == rhs.m_owner;
}

template<typename T, size_t sz>
bool static_array<T, sz>::iterator::operator!=(const static_array::iterator &rhs) {
  return !(*this == rhs);
}
