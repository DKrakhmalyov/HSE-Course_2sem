
//#include "static_array.h"
#ifdef _IMPL_

template <typename T, size_t sz>
static_array<T, sz>::static_array() : begin_(this), end_(this) {
  data.resize(sz);
  initialized.resize(sz);
  for (int i = 0; i < sz; i++) {
    data[i] = nullptr;
    initialized[i] = 0;
  }
  current_size_ = 0;
  size_ = sz;
}

template <typename T, size_t sz>
static_array<T, sz>::static_array(size_t sz_) : begin_(this), end_(this) {
  data.resize(sz_);
  initialized.resize(sz_);
  for (int i = 0; i < sz; i++) {
    data[i] = nullptr;
    initialized[i] = 0;
  }
  current_size_ = 0;
  size_ = sz_;
}

template <typename T, size_t sz>
size_t static_array<T, sz>::current_size() {
  return current_size_;
}

template <typename T, size_t sz>
size_t static_array<T, sz>::size() {
  return size_;
}

template <typename T, size_t sz>
void static_array<T, sz>::clear() {
  for (int i = 0; i < sz; i++) {
    if (initialized[i]) {
      delete data[i];
      data[i] = nullptr;
      initialized[i] = 0;
    }
  }
  current_size_ = 0;
  begin_ = static_array::iterator(this);
  end_ = static_array::iterator(this);
}

template <typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind,
                                                                    T &&obj) {
  if (initialized[ind]) {
    delete data[ind];
    data[ind] = nullptr;
    current_size_--;
  }
  data[ind] = new T(std::forward<T>(obj));
  initialized[ind] = 1;
  current_size_++;
  if ((!initialized[begin_.pos]) || ind < begin_.pos) {
    begin_.pos = ind;
  }
  if (end_.pos < ind) {
    end_.pos = ind;
  }
  return static_array::iterator(this, ind);
}

template <typename T, size_t sz>
template <class... Args>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(
    size_t ind, Args &&...args) {
  if (initialized[ind]) {
    delete data[ind];
    data[ind] = nullptr;
    current_size_--;
  }
  data[ind] = new T(std::forward<Args>(args)...);
  initialized[ind] = 1;
  current_size_++;
  if ((!initialized[begin_.pos]) || ind < begin_.pos) {
    begin_.pos = ind;
  }
  if (end_.pos < ind) {
    end_.pos = ind;
  }
  return static_array::iterator(this, ind);
}

template <typename T, size_t sz>
void static_array<T, sz>::erase(static_array::iterator it) {
  if (initialized[it.pos]) {
    current_size_--;
  }
  delete data[it.pos];
  initialized[it.pos] = 0;
  for (size_t i = it.pos + 1; i != 0; i = (i + 1) % size_) {
    it.pos = i;
    if (initialized[i]) {
      break;
    }
    if (i == size_ - 1) {
      begin_.pos = 0;
    }
  }
  for (size_t i = it.pos; i != 0; i--) {
    it.pos = i;
    if (initialized[i]) {
      break;
    }
    if (i == 1) {
      end_.pos = 0;
    }
  }
}

template <typename T, size_t sz>
T &static_array<T, sz>::at(size_t ind) {
  if (!initialized[ind]) {
    throw std::exception();
  }
  return *data[ind];
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
static_array<T, sz>::iterator::iterator(const iterator &other)
    : pos(other.pos), array(other.array) {}

template <typename T, size_t sz>
static_array<T, sz>::iterator::~iterator() {}

template <typename T, size_t sz>
typename static_array<T, sz>::iterator &
static_array<T, sz>::iterator::operator=(const iterator &other) {
  pos = other.pos;
  array = other.array;
  return *this;
}

template <typename T, size_t sz>
typename static_array<T, sz>::iterator &
static_array<T, sz>::iterator::operator++() {
  do {
    pos++;
  } while (pos < (array->end().pos) && !(array->initialized[pos]));
  return *this;
}

template <typename T, size_t sz>
typename static_array<T, sz>::iterator &
static_array<T, sz>::iterator::operator--() {
  do {
    pos--;
  } while (pos < array->size_ && (!(array->initialized[pos])));
  return *this;
}

template <typename T, size_t sz>
T *static_array<T, sz>::iterator::operator->() const {
  return &(array->at(pos));
}

template <typename T, size_t sz>
T &static_array<T, sz>::iterator::operator*() const {
  return array->at(pos);
}

template <typename T, size_t sz>
bool static_array<T, sz>::iterator::operator==(
    typename static_array<T, sz>::iterator const &b) const {
  return ((*this).array == b.array) && ((*this).pos == b.pos);
}

template <typename T, size_t sz>
bool static_array<T, sz>::iterator::operator!=(
    typename static_array<T, sz>::iterator const &b) const {
  return !((*this) == b);
}

template <typename T, size_t sz>
static_array<T, sz>::iterator::iterator(static_array<T, sz> *array_) {
  array = array_;
  pos = 0;
}

template <typename T, size_t sz>
static_array<T, sz>::iterator::iterator(static_array<T, sz> *array_,
                                        size_t pos_) {
  array = array_;
  pos = pos_;
}

#endif
