#include "static_array.h"
#include <stdexcept>
#include <vector>

template<typename T, size_t sz>
static_array<T,sz>::static_array()
    :array((T*)(operator new[](sz * sizeof(T)))),
    elem_exists(sz),
    a_capacity(sz),
    a_size(0){}

template<typename T, size_t sz>
static_array<T,sz>::static_array(size_t new_sz)
    :array((T*)(operator new[](sz * sizeof(T)))),
    elem_exists(new_sz),
    a_capacity(new_sz),
    a_size(0){}

template<typename T, size_t sz>
static_array<T,sz>::~static_array(){
    operator delete[](array, a_capacity * sizeof(T));
}

template<typename T, size_t sz>
inline size_t static_array<T,sz>::current_size() const{
    return a_size;
}

template<typename T, size_t sz>
inline size_t static_array<T,sz>::size() const{
    return a_capacity;
}

template<typename T, size_t sz>
void static_array<T,sz>::clear(){
    for(size_t i = 0; i < a_capacity; i++)
        if(elem_exists[i])
            array[i].~T();
    a_size = 0;
}


template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, T &&obj){
    if(!elem_exists[ind]){
        elem_exists[ind] = true;
        a_size++;
    }
    array[ind] = T(std::move(obj));
    return iterator(this, ind);
}

template<typename T, size_t sz>
template<class... Args>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind,  Args &&... args){
    if(!elem_exists[ind]){
        elem_exists[ind] = true;
        a_size++;
    }
    array[ind] = T(std::forward<Args>(args)...);
    return iterator(this, ind);
}

template<typename T, size_t sz>
void static_array<T, sz>::erase(static_array::iterator it){
    it->~T();
    elem_exists[it.it_index] = false;
    --a_size;
}

template<typename T, size_t sz>
T &static_array<T,sz>::at(size_t ind){
    if(!elem_exists[ind])
        throw std::runtime_error("Element doesnot exist");
    if(ind < 0 || ind >= a_capacity)
        throw std::out_of_range("Index is out of range or element doesn't exist");
    else
        return array[ind];
    
} 

template<typename T, size_t sz>
typename static_array<T,sz>::iterator static_array<T,sz>::begin(){
    for(size_t i = 0; i < a_capacity;i++)
        if(elem_exists[i])
            return iterator(this, i);
}

template<typename T, size_t sz>
typename static_array<T,sz>::iterator static_array<T,sz>::end(){
    for(size_t i = 0; i < a_capacity;i++)
        if(elem_exists[i])
            return iterator(this, ++i);
    return iterator(this, a_capacity);
}

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator(const iterator &other)
    :master(other.master),
    it_index(other.it_index){}

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator(static_array<T, sz>* array, size_t ind)
    :master(array),
    it_index(ind){}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator=(const iterator &other){
    master = other.master;
    it_index = other.it_index;

}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator++(){
    size_t i = it_index;
    do {
        i++;
        if(i >= master->a_capacity){
            it_index = i;
            return *this;
        }
    } while(it_index < master->a_capacity && !master->elem_exists[it_index]);
    return *this;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator--(){
    if(it_index == 0){
        this->it_index = master->a_capacity;
        return *this;
    }
    while(it_index > 0){
        --it_index;
        if(master->elem_exists[it_index])
            return *this;
    }
    this->it_index = master->a_capacity;
    return *this;
}

template<typename T, size_t sz>
T* static_array<T, sz>::iterator::operator->() const{
    return master->array + it_index;
}

template<typename T, size_t sz>
T &static_array<T, sz>::iterator::operator*() const{
    return *(master->array + it_index);
}

template<typename T, size_t sz>
bool operator==(const typename static_array<T, sz>::iterator& a, const typename static_array<T, sz>::iterator& b){
    return (a.it_index == b.it_index) && (a.master == b.master);
}

template<typename T, size_t sz>
bool operator!=(const typename static_array<T, sz>::iterator& a, const typename static_array<T, sz>::iterator& b){
    return !(a == b);
}