#ifdef _STATIC_ARRAY_IMPLEMENTATION_

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
inline size_t static_array<T, sz>::current_size() const {
  return this->_current_size;
}

template<typename T, size_t sz>
inline size_t static_array<T, sz>::size() const {
  return this->_copacity;
}

template<typename T, size_t sz>
inline void static_array<T, sz>::clear() {
  for (auto i = begin(); i != end(); ++i) {
    erase(i);
  }
}

template<typename T, size_t sz>
inline static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t index, T &&obj) {
  if (index >= _copacity) {
    throw std::out_of_range("static_array: Index out of range");
  }
  if (_initialized[index]) {
    erase(iterator(index, this));
  }
  new (_get_pointer_on_index(index)) T(std::forward<T>(obj));
  _initialized[index] = true;
  ++_current_size;
  return static_array::iterator(index, this);
}

template<typename T, size_t sz>
template<class... Args>
inline static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t index, Args &&... args) {
  if (index >= _copacity) {
    throw std::out_of_range("static_array: Index out of range");
  }
  if (_initialized[index]) {
    erase(iterator(index, this));
  }
  new (_get_pointer_on_index(index)) T(std::forward<Args>(args)...);
  _initialized[index] = true;
  ++_current_size;
  return static_array::iterator(index, this);
}

template<typename T, size_t sz>
inline void static_array<T, sz>::erase(static_array::iterator iter) {
  if (!_initialized[iter._index]) {
    throw std::runtime_error("static_array: Invalid iterator on erase");
  }
  iter->~T();
  --_current_size;
  _initialized[iter._index] = false;
}

template<typename T, size_t sz>
inline T& static_array<T, sz>::at(size_t index) {
  if (index >= _copacity) {
    throw std::out_of_range("static_array: Index out of range");
  }
  if (!_initialized[index]) {
    throw std::runtime_error("static_array: Value is not initialized");
  }
  return *_get_pointer_on_index(index);
}

template<typename T, size_t sz>
inline static_array<T, sz>::iterator static_array<T, sz>::begin() {
  auto iter = iterator(0, this);
  if (_copacity > 0 && !_initialized[0]) {
    ++iter;
  }
  return iter;
}

template<typename T, size_t sz>
inline static_array<T, sz>::iterator static_array<T, sz>::end() {
  return iterator(_copacity, this);
}

template<typename T, size_t sz>
inline T* static_array<T, sz>::_get_pointer_on_index(size_t index) const {
  return reinterpret_cast<T*>(this->_data) + index;
}


template<typename T, size_t sz>
inline static_array<T, sz>::iterator::iterator(size_t index, static_array* owner)
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
  if (_index > _owner->_copacity) {
    throw std::out_of_range("static_array::iterator: Cannot increment end iterator");
  }

  do {
    ++_index;
  } while (_index < _owner->_copacity && !_owner->_initialized[_index]);

  return *this;
}

template<typename T, size_t sz>
inline static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator--() {
  if (_index == 0) {
    throw std::out_of_range("static_array::iterator: Cannot dectrement _index == 0 iterator");
  }

  do {
    --_index;
  } while (_index > 0 && !_owner->_initialized[_index]);

  return *this;
}

template<typename T, size_t sz>
inline T* static_array<T, sz>::iterator::operator->() {
  if (!_owner->_initialized[_index]) {
    throw std::runtime_error("static_array: Cannot access invalid iterator");
  }
  return _owner->_get_pointer_on_index(_index);
}

template<typename T, size_t sz>
inline T& static_array<T, sz>::iterator::operator*() {
  if (!_owner->_initialized[_index]) {
    throw std::runtime_error("static_array: Cannot access invalid iterator");
  }
  return *_owner->_get_pointer_on_index(_index);
}

template<typename T, size_t sz>
inline bool static_array<T, sz>::iterator::operator==(const iterator& other) const {
  return this->_index == other._index && this->_owner == other._owner;
}

template<typename T, size_t sz>
inline bool static_array<T, sz>::iterator::operator!=(const iterator& other) const {
  return !(*this == other);
}

#endif // _STATIC_ARRAY_IMPLEMENTATION_