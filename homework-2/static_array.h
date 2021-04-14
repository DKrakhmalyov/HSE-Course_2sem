//
// govnocode created by chap4ev on 14.04.2021
//

#ifndef _HOMEWORK_2_STATIC_ARRAY_H_
#define _HOMEWORK_2_STATIC_ARRAY_H_

#include <stdexcept>
#include <memory>
#include <vector>

template<typename T, size_t sz = 0>
class static_array {
 public:
  class iterator {
   protected:
    T* _item;
    static_array* _owner;
    iterator(T* item, static_array* owner);

   public:
    iterator(const iterator& other) = default;

    ~iterator() = default;

    iterator& operator=(const iterator& other);

    iterator& operator++();
    iterator& operator--();

    T* operator->() const;
    T& operator*() const;

    bool operator==(const iterator& other);
    bool operator!=(const iterator& other);

    friend class static_array;
  };

  static_array();
  explicit static_array(size_t copacity);

  ~static_array();

  size_t current_size();
  size_t size();
  void clear();

  T& at(size_t index);

  static_array::iterator emplace(size_t index, T &&obj);

  template<class... Args>
  static_array::iterator emplace(size_t index, Args &&... args);

  void erase(static_array::iterator iter);

  static_array::iterator begin();
  static_array::iterator end();

 protected:
  char* _data;
  std::vector<bool> _initialized;
  size_t _copacity;
  size_t _current_size;

  T* _get_pointer_on_index(const size_t& index) const;

  void _check_bounds(const size_t& index) const;
  void _check_is_initialized(const size_t& index) const;

  int _get_next_avaliable_index(int index) const;
  int _get_prev_avaliable_index(int index) const;
};

#define _STATIC_ARRAY_IMPL_
#include "static_array.cpp"

#endif //_HOMEWORK_2_STATIC_ARRAY_H_