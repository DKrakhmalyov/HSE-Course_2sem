//
// Created by Denis on 12.03.2021.
//

#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H

#include <cstdio>
#include <array>
#include <vector>

template<typename T, size_t sz = 0>
class static_array {
public:
  class iterator {
  public:
    std::size_t m_pos;
    static_array<T, sz> *m_owner;

    iterator(std::size_t pos, static_array<T, sz> *owner);

    iterator(const iterator &);

    ~iterator();

    iterator &operator=(const iterator &);

    iterator &operator++();

    iterator &operator--();

    T *operator->() const;

    T &operator*() const;

    bool operator==(const iterator &);

    bool operator!=(const iterator &);
  };

  static_array();

  explicit static_array(size_t capacity);

  ~static_array();

  size_t current_size();

  size_t size();

  void clear();

  static_array::iterator emplace(size_t ind, T &&obj);

  template<class... Args>
  static_array::iterator emplace(size_t ind, Args &&... args);

  void erase(static_array::iterator);

  T &at(size_t ind);

  static_array::iterator begin();

  static_array::iterator end();

private:
  void _precond_index(std::size_t index) const;
  void _precond_available(std::size_t index) const;

  // Bytes for data stored there.
  int8_t *m_data{nullptr};

  // Initialized element's indices storage.
  std::vector<bool> m_init;

  // Max capacity of the array.
  std::size_t m_capacity{0};

  // Current size of the array.
  std::size_t m_size{0};

  iterator _int_write(size_t index, T&&value);
  T *_int_at(size_t index) const;
};

#endif //HOMEWORK_2_STATIC_ARRAY_H
