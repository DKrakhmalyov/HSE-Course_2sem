//
// Created by Denis on 12.03.2021.
//

#include "static_array.h"
#ifdef _IMPL_

template <typename T, size_t sz>
static_array<T, sz>::static_array(size_t sz_) : begin_(this), end_(this) {
 used.resize(sz_); 
 data.resize(sz_);
  for (int i = 0; i < sz; i++) {
    data[i] = nullptr;
    used[i] = 0;
  }
  curr_size_ = 0;
  size_ = sz_;
}

template <typename T, size_t sz>
static_array<T, sz>::static_array() : begin_(this), end_(this) {
  used.resize(sz);
  data.resize(sz);
  for (int i = 0; i < sz; i++) {
    data[i] = nullptr;
    used[i] = 0;
  }
  curr_size_ = 0;
  size_ = sz;
}

template <typename T, size_t sz>
size_t static_array<T, sz>::size() {
  return size_;
}

template <typename T, size_t sz>
size_t static_array<T, sz>::current_size() {
  return curr_size_;
}

template <typename T, size_t sz>
void static_array<T, sz>::clear() {
  for (int i = 0; i < sz; i++) {
    if (used[i]) {
      delete data[i];
     used[i] = 0; 
     data[i] = nullptr; 
    }
  }
  begin_ = static_array::iterator(this);
  end_ = static_array::iterator(this);
  curr_size_ = 0;
}

template <typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, T &&obj) {
  if (used[ind]) {
    delete data[ind];
    curr_size_--;
    data[ind] = nullptr;
  }
  used[ind] = 1;
  data[ind] = new T(std::forward<T>(obj));
  curr_size_++;
  if (end_.pos < ind) {
    end_.pos = ind;
  }
  if ((!used[begin_.pos]) || ind < begin_.pos) {
    begin_.pos = ind;
  }
  return static_array::iterator(this, ind);
}

template <typename T, size_t sz>
template <class... Args>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, Args &&...args) {
  if (used[ind]) {
    delete data[ind];
    curr_size_--;
    data[ind] = nullptr;
  }
  used[ind] = 1; 
  data[ind] = new T(std::forward<Args>(args)...);
  curr_size_++;
  if (end_.pos < ind) {
    end_.pos = ind;
  }
  if ((!used[begin_.pos]) || ind < begin_.pos) {
    begin_.pos = ind;
  }
  return static_array::iterator(this, ind);
}

template <typename T, size_t sz>
T &static_array<T, sz>::at(size_t ind) {
  if (!used[ind]) {
    throw std::exception();
  }
  return *data[ind];
}

template <typename T, size_t sz>
void static_array<T, sz>::erase(static_array::iterator it) {
  delete data[it.pos];
  if (used[it.pos]) {
    curr_size_--;
  }
  used[it.pos] = 0;
    size_t i=it.pos+1;
    while(i!=0){
      it.pos = i;
     if (used[i]) {
       break;
     }
     if (i == size_ - 1) {
       begin_.pos = 0;
      }
    i=(i + 1) % size_;
  }
  i=it.pos;
  while(i!=0){
    it.pos = i;
    if (used[i]) {
      break;
    }
    if (i == 1) {
      end_.pos = 0;
    }
    i--;
  }
}



template <typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::begin() {
  return begin_;
}

template <typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::end() {
  static_array::iterator output = end_;
  output.pos++;
  return output;                                                  
}

template <typename T, size_t sz>
static_array<T, sz>::iterator::iterator(const iterator &other): pos(other.pos), array(other.array) {}

template <typename T, size_t sz>
static_array<T, sz>::iterator::~iterator() {}

template <typename T, size_t sz>
typename static_array<T, sz>::iterator &
static_array<T, sz>::iterator::operator=(const iterator &other) {
  array = other.array;
  pos = other.pos;
  return *this;
}

template <typename T, size_t sz>
typename static_array<T, sz>::iterator &
static_array<T, sz>::iterator::operator++() {
  while (!(array->used[pos]) && pos < (array->end().pos)){
    pos++;
  }
  pos++;
  return *this;
}

template <typename T, size_t sz>
typename static_array<T, sz>::iterator &
static_array<T, sz>::iterator::operator--() {
   while ((!(array->used[pos])) && pos < array->size_){
    pos--;
  }
  pos--;
  return *this;
}

template <typename T, size_t sz>
T &static_array<T, sz>::iterator::operator*() const {
  return array->at(pos);
}

template <typename T, size_t sz>
T *static_array<T, sz>::iterator::operator->() const {
  return &(array->at(pos));
}

template <typename T, size_t sz>
bool static_array<T, sz>::iterator::operator==(
    typename static_array<T, sz>::iterator const &b) const {
  return ((*this).pos == b.pos) && ((*this).array == b.array);
}

template <typename T, size_t sz>
bool static_array<T, sz>::iterator::operator!=(
    typename static_array<T, sz>::iterator const &b) const {
  return !((*this) == b);
}

template <typename T, size_t sz>
static_array<T, sz>::iterator::iterator(static_array<T, sz> *array_,size_t pos_) {
  pos = pos_;
  array = array_;
}

template <typename T, size_t sz>
static_array<T, sz>::iterator::iterator(static_array<T, sz> *array_) {
  pos = 0;
  array = array_; 
}

#endif

