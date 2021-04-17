//
// Created by Denis on 12.03.2021.
//

#pragma once

#ifndef STATIC_ARRAY_H
#define STATIC_ARRAY_H

#include <algorithm>
#include <bitset>
#include <limits>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

template<typename T, size_t capacity = 0>
class static_array {
  friend class iterator;
 public:
  class iterator {
    friend static_array<T, capacity>;

   public:
    iterator(const iterator &);

    ~iterator();

    iterator &operator=(const iterator &);

    iterator &operator++();

    iterator &operator--();

    T *operator->() const;

    T &operator*() const;

    bool operator==(iterator const &other) const;
    
    bool operator!=(iterator const& other) const;

   private:
    iterator(static_array<T, capacity>* container, size_t index);

    static size_t GetNextInitialized(const static_array<T, capacity>* container, size_t starting_index);
    static size_t GetPreviousInitialized(const static_array<T, capacity>* container, size_t starting_index);
    
   private:
    static_array<T, capacity> *m_container;
    size_t m_index;
  };

  template <size_t cur_capacity = capacity,
            typename std::enable_if<(cur_capacity == 0), int>::type = 0>
  static_array(size_t size)
      : m_data(new uint8_t[size * sizeof(T)]),
        m_has_value(size),
        m_capacity(size),
        m_size(0) {}

  template <size_t cur_capacity = capacity,
            typename std::enable_if<(cur_capacity > 0), int>::type = 0>
  static_array()
      : m_data(new uint8_t[capacity * sizeof(T)]),
        m_has_value(capacity),
        m_capacity(capacity),
        m_size(0) {}

  size_t current_size() const;

  size_t size() const;

  void clear();

  template <typename... Args>
  static_array::iterator emplace(size_t index, Args&&... args);

  static_array::iterator emplace(size_t index, T&& element);
  
  void erase(static_array::iterator iterator);

  T &at(size_t index);

  static_array::iterator begin();

  static_array::iterator end();

  ~static_array();
  
 private:
  uint8_t* m_data;
  std::vector<bool> m_has_value;
  size_t m_capacity;
  size_t m_size;
};

#include "static_array.cpp"

#endif
