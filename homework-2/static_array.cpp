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
  for (auto i = begin(); i != end(); ++i) {
    erase(i);
  }
}

template<typename T, size_t sz>
inline static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, T &&obj) {
  _check_bounds(ind);
  if (_initialized[ind]) {
    _get_pointer_on_index(ind)->~T();
    --_current_size;
  }
  new (_data + sizeof(T) * ind) T(std::forward<T>(obj));
  _initialized[ind] = true;
  ++_current_size;
  return static_array::iterator(_get_pointer_on_index(ind), this);
}

template<typename T, size_t sz>
template<class... Args>
inline static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, Args &&... args) {
  _check_bounds(ind);
  if (_initialized[ind]) {
    _get_pointer_on_index(ind)->~T();
    --_current_size;
  }
  new (_data + sizeof(T) * ind) T(std::forward<Args>(args)...);
  _initialized[ind] = true;
  ++_current_size;
  return static_array::iterator(_get_pointer_on_index(ind), this);
}

template<typename T, size_t sz>
inline void static_array<T, sz>::erase(static_array::iterator iter) {
  iter->~T();
  --_current_size;

}

template<typename T, size_t sz>
inline T& static_array<T, sz>::at(size_t ind) {
  _check_bounds(ind);
  _check_is_initialized(ind);
  return *_get_pointer_on_index(ind);
}

template<typename T, size_t sz>
inline static_array<T, sz>::iterator static_array<T, sz>::begin() {
  return static_array::iterator(
           _get_pointer_on_index(_get_next_avaliable_index(-1)),
           this
         );
}

template<typename T, size_t sz>
inline static_array<T, sz>::iterator static_array<T, sz>::end() {
  return static_array::iterator(_get_pointer_on_index(_copacity), this);
}

template<typename T, size_t sz>
inline void static_array<T, sz>::_check_bounds(const size_t& ind) const {
  if (ind >= _copacity)
    throw std::out_of_range("static_array: Index out of range");
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
inline static_array<T, sz>::iterator::iterator(T* item, static_array* owner)
  : _item(item)
  , _owner(owner)
{ };

template<typename T, size_t sz>
inline static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator=(const iterator& other) {
  _item = other._item;
  _owner = other._owner;
  return *this;
}

template<typename T, size_t sz>
inline static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator++() {
  _item = _owner->_get_pointer_on_index(
            _owner->_get_next_avaliable_index(_item - reinterpret_cast<T*>(_owner->_data))
          );
  return *this;
}

template<typename T, size_t sz>
inline static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator--() {
  auto prev_index = _owner->_get_prev_avaliable_index(_item - _owner->_data);
  if (prev_index == -1) {
    _item = _owner->_get_pointer_on_index(_owner->_copacity);
  }
  _item = _owner->_get_pointer_on_index(prev_index);
  return *this;
}

template<typename T, size_t sz>
inline T* static_array<T, sz>::iterator::operator->() const {
  return _item;
}

template<typename T, size_t sz>
inline T& static_array<T, sz>::iterator::operator*() const {
  return *_item;
}

template<typename T, size_t sz>
inline bool static_array<T, sz>::iterator::operator==(const iterator& other) {
  return this->_item == other._item && this->_owner == other._owner;
}

template<typename T, size_t sz>
inline bool static_array<T, sz>::iterator::operator!=(const iterator& other) {
  return !(*this == other);
}

#endif // _STATIC_ARRAY_IMPL_