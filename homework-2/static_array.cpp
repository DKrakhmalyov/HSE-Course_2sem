#include "static_array.h"

template<typename T, size_t sz>
bool static_array<T, sz>::iterator::operator== (const static_array<T, sz>::iterator& rhs) {
    return (m_place == rhs.m_place) && (m_arr.m_elements == rhs.m_arr.m_elements);
}

template<typename T, size_t sz>
bool static_array<T, sz>::iterator::operator!= (const static_array<T, sz>::iterator& rhs) {
    return !(*this == rhs);
}

template<typename T, size_t sz>
static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator++ () {
    if (m_place == m_arr.size()) {
        throw std::out_of_range("Unable to increment iterator");
    }
    
    m_place = static_array<T, sz>::iterator::at(m_place+1, m_arr);
    return *this;
}

template<typename T, size_t sz>
static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator-- () {
    if (m_place == 0) {
        throw std::out_of_range("Unable to decrement iterator");
    }

    m_place = iterator::at_up(m_place-1, m_arr);
    return *this;
}

template<typename T, size_t sz>
T* static_array<T, sz>::iterator::operator-> () const {
    if (!m_arr.m_array_init[m_place]) {
        throw std::out_of_range("Unable to dereference iterator");
    }

    return &m_arr.get_elem(m_place);
}

template<typename T, size_t sz>
T& static_array<T, sz>::iterator::operator* () const {
    if (!m_arr.m_array_init[m_place]) {
        throw std::out_of_range("Unable to dereference iterator");
    }
    
    return m_arr.get_elem(m_place);
}


template<typename T, size_t sz>
size_t static_array<T, sz>::iterator::at (size_t from, static_array<T, sz>& arr) {
    size_t final = arr.end().position();
    for(size_t i = from; i < final; i++) {
        if (arr.m_array_init[i]) {
            return i;
        }
    }

    return final;
}

template<typename T, size_t sz>
size_t static_array<T, sz>::iterator::at_up (size_t from, static_array<T, sz>& arr) {
    for(size_t i = from; i >= 0; i--) {
        if (arr.m_array_init[i]) {
            return i;
        }
    }

    throw std::out_of_range("out of range at iterator::at_up");
}

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator (size_t pos, static_array<T, sz>& arr) : m_place(pos), m_arr(arr) {}

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator (const  static_array<T, sz>::iterator& it) : m_place(it.m_place), m_arr(it.m_arr) {}

template<typename T, size_t sz>
static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator= (const iterator & it) {
    m_place = it.m_place;
    m_arr = it.m_arr;
}

template<typename T, size_t sz>
size_t static_array<T, sz>::iterator::position () {
    return m_place;
}

template<typename T, size_t sz>
static_array<T, sz>::iterator::~iterator() = default;



///////////////////////////////////////////////////////////



template<typename T, size_t sz>
static_array<T, sz>::static_array (size_t size) {

    m_array_init = new bool[size];
    m_elements = reinterpret_cast<T*>(new char[size*sizeof(T)]);
    m_filled = 0;
    m_last_element = 0;
    m_size = size;

    std::fill(m_array_init, m_array_init+size, 0);
}

template<typename T, size_t sz>
static_array<T, sz>::static_array () : static_array(sz) { }

template<typename T, size_t sz>
size_t static_array<T, sz>::current_size () {
    return m_filled;
}

template<typename T, size_t sz>
size_t static_array<T, sz>::size () {
    return m_size;
}


template<typename T, size_t sz>
static_array<T,sz>::iterator static_array<T, sz>::emplace (size_t ind, T &&obj) { 
    check_and_destroy(ind);

    m_last_element = std::max(ind, m_last_element);

    new (&m_elements[ind]) T(std::forward<T>(obj));
    m_array_init[ind] = 1;
    ++m_filled;

    return static_array<T, sz>::iterator(ind, *this);
}


template<typename T, size_t sz>
template<class... Args> 
static_array<T,sz>::iterator static_array<T, sz>::emplace (size_t ind, Args&&... objs) {  
    check_and_destroy(ind);

    m_last_element = std::max(ind, m_last_element);

    new (&m_elements[ind]) T(std::forward<Args>(objs)...);
    m_array_init[ind] = 1;
    ++m_filled;

    return static_array<T,sz>::iterator(ind, *this);
}

template<typename T, size_t sz>
void static_array<T, sz>::erase (static_array<T,sz>::iterator it) { 
    check_and_destroy(it.position());
    m_array_init[it.position()] = 0;
    if (!m_filled) {
        m_last_element = 0;
    }
    else if (it.position() < m_last_element) {
        m_last_element = iterator::at_up(m_size-1, *this);
    }
}

template<typename T, size_t sz>
void static_array<T, sz>::check_and_destroy(size_t pos)
{
    if (!m_array_init[pos]) {
        return;
    }
    --m_filled;

    m_elements[pos].~T();
}


template<typename T, size_t sz>
T& static_array<T,sz>::get_elem (size_t pos) { 
    return m_elements[pos];
}

template<typename T, size_t sz>
T& static_array<T,sz>::at(size_t ind) {
    if (ind > m_size) {
        throw std::range_error("index must be in [0, size-1]");
    }
    if (!m_array_init[ind]) {
        throw std::runtime_error("not initialized yet");
    }

    return m_elements[ind];
}

template<typename T, size_t sz>
static_array<T,sz>::iterator static_array<T,sz>::begin() { 
    if (!m_filled) {
        throw std::runtime_error("not initialized yet");
    }
    return static_array<T,sz>::iterator(iterator::at(0, *this), *this);
}

template<typename T, size_t sz>
static_array<T,sz>::iterator static_array<T,sz>::end() { 
    if (!m_filled) {
        throw std::runtime_error("not initialized yet");
    }
    return static_array<T,sz>::iterator(m_last_element+1, *this);
}

template<typename T, size_t sz>
void static_array<T, sz>::clear () { 
    for(size_t i = 0; i < m_size; i++) {
        check_and_destroy(i);
    }

    m_last_element = 0;
}

template<typename T, size_t sz>
static_array<T,sz>::~static_array() {
    clear();
    delete [] m_array_init;
    delete [] m_elements;
}
