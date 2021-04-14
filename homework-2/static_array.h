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
    size_t _index;
    static_array* _owner;
    iterator(size_t _index, static_array* owner);

   public:
    iterator(const iterator& other) = default;

    ~iterator() = default;

    iterator& operator=(const iterator& other);

    iterator& operator++();
    iterator& operator--();

    T* operator->();
    T& operator*();

    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;

    friend class static_array;
  };

  static_array();
  explicit static_array(size_t copacity);

  ~static_array();

  size_t current_size() const;
  size_t size() const;
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

  T* _get_pointer_on_index(const size_t index) const;
};

#define _STATIC_ARRAY_IMPLEMENTATION_
#include "static_array.cpp"

#endif //_HOMEWORK_2_STATIC_ARRAY_H_