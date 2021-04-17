
#include "static_array.h"

template <typename T, size_t sz>
static_array<T, sz>::iterator::iterator(T** newCur, T** beginI, T**endI)
{
    curr = newCur;
    begin = beginI;
    end = endI;
}

template <typename T, size_t sz>
static_array<T, sz>::iterator::iterator(const static_array<T, sz>::iterator& newI)
{
    this->curr = newI.curr;
}

template <typename T, size_t sz>
static_array<T, sz>::iterator::~iterator() {}

template <typename T, size_t sz>
static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator=(const static_array<T, sz>::iterator& it)
{
    this->curr = it.curr;
    return *this;
}

template <typename T, size_t sz>
static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator++()
{
    if (this->curr != this->end)
    {
        this->curr++;
    }
    while (this->curr != this->end && !*this->curr)
    {
        this->curr++;
    }
    return *this;
}

template <typename T, size_t sz>
static_array<T, sz>::iterator& static_array<T, sz>::iterator::operator--()
{
    if (this->curr != this->begin)
    {
        this->curr--;
    }
    while (this->curr != this->begin && !*this->curr)
    {
        this->curr--;
    }
    return *this;
}

template <typename T, size_t sz>
T* static_array<T, sz>::iterator::operator->() const
{
    return *this->curr;
}

template <typename T, size_t sz>
T& static_array<T, sz>::iterator::operator*() const
{
    return **this->curr;
}

template <typename T, size_t sz>
bool static_array<T, sz>::iterator::operator==(const typename static_array<T, sz>::iterator& it)
{
    return this->curr == it.curr;
}

template <typename T, size_t sz>
bool static_array<T, sz>::iterator::operator!=(const typename static_array<T, sz>::iterator& it)
{
    return !(*this == it);
}

template <typename T, size_t sz>
static_array<T, sz>::static_array() : static_array(sz){}

template <typename T, size_t sz>
static_array<T, sz>::static_array(size_t sz2)
{
    if (sz2 < sz)
    {
        sz2 = sz;
    }
    this->data = new T* [sz2 + 1];
    this->curSize = sz2;
    this->count = 0;
    for (int i = 0; i < this->curSize; i++)
    {
        this->data[i] = nullptr;
    }
}

template <typename T, size_t sz>
static_array<T, sz>::static_array(const static_array<T, sz>& newArr)
{
    this->data = new T* [newArr.curSize + 1];
    this->curSize = newArr.curSize;
    this->count = newArr.count;
    for (int i = 0; i < newArr.curSize; i++)
    {
        this->data[i] = new T(*newArr.data[i]);
    }
}
template <typename T, size_t sz>
static_array<T, sz>::static_array(static_array<T, sz>&& newArr)
{
    this->data = newArr.data;
    newArr.data = 0;
    this.curSize = newArr.curSize;
    this.count = newArr.count;
}

template <typename T, size_t sz>
static_array<T, sz>& static_array<T, sz>::operator=(const static_array<T, sz>& newArr)
{
    this->clear();
    this->data = new T* [newArr.curSize + 1];
    this->curSize = newArr.curSize;
    this->count = newArr.count;
    for (int i = 0; i < newArr.curSize; i++)
    {
        this->data[i] = new T(*newArr.data[i]);
    }
    return *this;
}
template <typename T, size_t sz>
static_array<T, sz>& static_array<T, sz>::operator=(static_array<T, sz>&& newArr)
{
    this->clear();
    this->data = newArr.data;
    newArr.data = nullptr;
    this.curSize = newArr.curSize;
    this.count = newArr.count;
    return *this;
}

template <typename T, size_t sz>
size_t static_array<T, sz>::current_size()
{
    return this->count;
}

template <typename T, size_t sz>
size_t static_array<T, sz>::size()
{
    return this->curSize;
}

template <typename T, size_t sz>
void static_array<T, sz>::clear()
{
    for (int i = 0; i < this->curSize; i++)
    {
        if (this->data[i])
        {
            delete this->data[i];
            this->data[i] = nullptr;
        }
    }
    delete[] this->data;
    this->data = nullptr;
    this->curSize = 0;
    this->count = 0;
}
template <typename T, size_t sz>
static_array<T, sz>::~static_array()
{
    this->clear();
}

template <typename T, size_t sz>
void static_array<T, sz>::erase(static_array<T, sz>::iterator it)
{
    delete *(it.curr);
    *(it.curr) = nullptr;
    this->count--;
}

template <typename T, size_t sz>
T& static_array<T, sz>::at(size_t ind)
{
    if (!this->data[ind])
    {
        throw "Given index is out of static_array range";
    }
    return *this->data[ind];
}

template <typename T, size_t sz>
static_array<T, sz>::iterator static_array<T, sz>::begin()
{
    return static_array<T, sz>::iterator(this->data, this->data, this->data + this->curSize);
}

template <typename T, size_t sz>
static_array<T, sz>::iterator static_array<T, sz>::end()
{
    return static_array<T, sz>::iterator(this->data + this->curSize, this->data, this->data + this->curSize);
}

template <typename T, size_t sz>
static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, T&& obj)
{
    this->count += (!this->data[ind]);
    this->data[ind] = new T(std::forward<T>(obj));
    return static_array<T, sz>::iterator(this->data + ind, this->data, this->data + this->curSize);
}

template <typename T, size_t sz>
template <class... Args>
static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, Args&& ...args)
{
    this->count += (!this->data[ind]);
    this->data[ind] = new T(std::forward<Args>(args)...);
    return static_array<T, sz>::iterator(this->data + ind, this->data, this->data + this->curSize);
}