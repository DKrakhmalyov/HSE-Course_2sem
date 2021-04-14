#ifdef _STATIC_ARRAY_IMPL_

template<typename T, size_t sz>
inline static_array<T, sz>::static_array()
  : static_array(sz)
{ }

template<typename T, size_t sz>
inline static_array<T, sz>::static_array(size_t copacity)
  : _copacity(copacity)
  , _current_size(0) {
  _data = new char[copacity * sizeof(T)];
  _initialized.resize(copacity);
}

template<typename T, size_t sz>
inline static_array<T, sz>::~static_array() {
  clear();
  delete [] _data;
}

template<typename T, size_t sz>
inline size_t static_array<T, sz>::current_size() {
  return this->_current_size;
}

template<typename T, size_t sz>
inline size_t static_array<T, sz>::size() {
  return this->_copacity;
}

template<typename T, size_t sz>
inline void static_array<T, sz>::clear() {
  for (size_t index = 0; index < _copacity; ++index){
    if (_initialized[index]){
      _get_pointer_on_index(index)->~T();
      --_current_size;
      _initialized[index] = false;
    }
  }
}

template<typename T, size_t sz>
inline static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, T &&obj) {
  if (ind >= _copacity){
    throw std::out_of_range("static_array: Index out of range");
  }
  if (_initialized[ind]) {
    _get_pointer_on_index(ind)->~T();
    --_current_size;
  }
  new (_data + sizeof(T) * ind) T(std::forward<T>(obj));
  _initialized[ind] = true;
  ++_current_size;
  return static_array::iterator(ind, this);
}

template<typename T, size_t sz>
template<class... Args>
inline static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, Args &&... args) {
  if (ind >= _copacity){
    throw std::out_of_range("static_array: Index out of range");
  }
  if (_initialized[ind]) {
    _get_pointer_on_index(ind)->~T();
    --_current_size;
  }
  new (_data + sizeof(T) * ind) T(std::forward<Args>(args)...);
  _initialized[ind] = true;
  ++_current_size;
  return static_array::iterator(ind, this);
}

template<typename T, size_t sz>
inline void static_array<T, sz>::erase(static_array::iterator iter) {
  iter->~T();
  --_current_size;
  _initialized[iter._index] = false;
}

template<typename T, size_t sz>
inline T& static_array<T, sz>::at(size_t ind) {
  if (ind >= _copacity){
    throw std::out_of_range("static_array: Index out of range");
  }
  _check_is_initialized(ind);
  return *_get_pointer_on_index(ind);
}

template<typename T, size_t sz>
inline static_array<T, sz>::iterator static_array<T, sz>::begin() {
  return static_array::iterator(_get_next_avaliable_index(-1), this);
}

template<typename T, size_t sz>
inline static_array<T, sz>::iterator static_array<T, sz>::end() {
  return static_array::iterator(_copacity, this);
}

template<typename T, size_t sz>
inline void static_array<T, sz>::_check_is_initialized(const size_t& ind) const {
  if (!_initialized[ind])
    throw std::runtime_error("static_array: Value is not initialized");
}

template<typename T, size_t sz>
inline int static_array<T, sz>::_get_next_avaliable_index(int index) const {
  for (++index; index < _copacity; ++index)
    if (_initialized[index])
      break;
  return index;
}

template<typename T, size_t sz>
inline int static_array<T, sz>::_get_prev_avaliable_index(int index) const {
  for (--index; index >= 0; --index)
    if (_initialized[index])
      break;
  return index;
}

template<typename T, size_t sz>
inline T* static_array<T, sz>::_get_pointer_on_index(const size_t& index) const {
  return reinterpret_cast<T*>(this->_data) + index;
}


template<typename T, size_t sz>
inline static_array<T, sz>::iterator::iterator(size_t& index, static_array* owner)
  : _index(index)
  , _owner(owner)
{ };

template<typename T, size_t sz>
inline static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator=(const iterator& other) {
  _index = other._index;
  _owner = other._owner;
  return *this;
}

template<typename T, size_t sz>
inline static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator++() {
  _index = _owner->_get_next_avaliable_index(_index);
  return *this;
}

template<typename T, size_t sz>
inline static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator--() {
  auto prev_index = _owner->_get_prev_avaliable_index(_index);
  if (prev_index == -1) {
    _index = _copacity;
  }
  _index = prev_index;
  return *this;
}

template<typename T, size_t sz>
inline T* static_array<T, sz>::iterator::operator->() const {
  return _get_pointer_on_index(_index);
}

template<typename T, size_t sz>
inline T& static_array<T, sz>::iterator::operator*() const {
  return *_get_pointer_on_index(_index);
}

template<typename T, size_t sz>
inline bool static_array<T, sz>::iterator::operator==(const iterator& other) {
  return this->_index == other._index && this->_owner == other._owner;
}

template<typename T, size_t sz>
inline bool static_array<T, sz>::iterator::operator!=(const iterator& other) {
  return !(*this == other);
}

#endif // _STATIC_ARRAY_IMPL_