#if defined(STATIC_ARRAY_IMPL)

template<typename T, size_t size_>
template<typename... Args>
T* static_array<T, size_>::construct_at(T* p, Args&&... args)
{
    return ::new (const_cast<void*>(static_cast<const volatile void*>(p)))
        T(std::forward<Args>(args)...);
}

template<typename T, size_t size_>
inline T* static_array<T, size_>::get_pointer(size_t index) const
{
    return std::launder(reinterpret_cast<T*>(this->data.get() + index));
}

template<typename T, size_t size_>
inline void static_array<T, size_>::erase_if_exists(size_t index)
{
    if (this->valid(index))
    {
        std::destroy_at(this->get_pointer(index));
        this->allocated[index] = false;
        this->current_count--;
    }
}

template<typename T, size_t size_>
inline static_array<T, size_>::static_array()
    : static_array(size_)
{
}

template<typename T, size_t size_>
inline static_array<T, size_>::static_array(size_t capacity)
    : total_capacity(capacity), current_count(0)
{
    this->data = std::make_unique<element_storage_t[]>(capacity);
    this->allocated = std::make_unique<bool[]>(capacity);
    std::fill(this->allocated.get(), this->allocated.get() + capacity, false);
}

template<typename T, size_t size_>
inline static_array<T, size_>::~static_array()
{
    this->clear();
}

template<typename T, size_t size_>
inline size_t static_array<T, size_>::current_size() const
{
    return this->current_count;
}

template<typename T, size_t size_>
inline size_t static_array<T, size_>::size() const
{
    return this->total_capacity;
}

template<typename T, size_t size_>
inline bool static_array<T, size_>::valid(size_t index) const
{
    return index < this->total_capacity && this->allocated[index];
}

template<typename T, size_t size_>
inline void static_array<T, size_>::clear()
{
    if (this->data != nullptr)
    {
        for (size_t i = 0; i < this->total_capacity; i++)
        {
            this->erase_if_exists(i);
        }
    }
}

template<typename T, size_t size_>
inline T& static_array<T, size_>::at(size_t index)
{
    if (!this->valid(index))
    {
        throw std::range_error("cannot access not allocated object");
    }
    return *this->get_pointer(index);
}

template<typename T, size_t size_>
inline const T& static_array<T, size_>::at(size_t index) const
{
    if (!this->valid(index))
    {
        throw std::range_error("cannot access not allocated object");
    }
    return *this->get_pointer(index);
}

template<typename T, size_t size_>
template<typename... Args>
inline typename static_array<T, size_>::iterator static_array<T, size_>::emplace(size_t index, Args&&... args)
{
    this->erase_if_exists(index);
    construct_at(this->get_pointer(index), std::forward<Args>(args)...);
    this->allocated[index] = true;
    this->current_count++;
    return iterator(this, index);
}

template<typename T, size_t size_>
inline typename static_array<T, size_>::iterator static_array<T, size_>::emplace(size_t index, T&& object)
{
    this->erase_if_exists(index);
    construct_at(this->get_pointer(index), std::forward<T>(object));
    this->allocated[index] = true;
    this->current_count++;
    return iterator(this, index);
}

template<typename T, size_t size_>
inline void static_array<T, size_>::erase(static_array::iterator it)
{
    if (!this->valid(it.index))
    {
        throw std::range_error("cannot erase not allocated object");
    }
    this->erase_if_exists(it.index);
}

template<typename T, size_t size_>
inline typename static_array<T, size_>::iterator static_array<T, size_>::begin()
{
    iterator it = iterator(this, 0);
    if (this->size() > 0 && !this->valid(0))
    {
        ++it;
    }
    return it;
}

template<typename T, size_t size_>
inline typename static_array<T, size_>::iterator static_array<T, size_>::end()
{
    iterator it = iterator(this, this->total_capacity);
    return it;
}

template<typename T, size_t size_>
inline static_array<T, size_>::iterator::iterator(static_array<T, size_>* container, size_t index)
    : container(container), index(index)
{
}

template<typename T, size_t size_>
inline static_array<T, size_>::iterator::iterator()
    : iterator(nullptr, 0)
{
}

template<typename T, size_t size_>
inline T* static_array<T, size_>::iterator::operator->() const
{
    return std::addressof(this->container->at(index));
}

template<typename T, size_t size_>
inline T& static_array<T, size_>::iterator::operator*() const
{
    return this->container->at(index);
}

template<typename T, size_t size_>
inline bool static_array<T, size_>::iterator::operator==(const iterator& it) const
{
    return this->container == it.container && this->index == it.index;
}

template<typename T, size_t size_>
inline bool static_array<T, size_>::iterator::operator!=(const iterator& it) const
{
    return !(*this == it);
}

template<typename T, size_t size_>
inline typename static_array<T, size_>::iterator& static_array<T, size_>::iterator::operator++()
{
    if (this->index == this->container->size())
    {
        throw std::range_error("cannot increment end iterator");
    }

    do
    {
        this->index++;
    } while (this->index < this->container->size() && !this->container->valid(this->index));
    return *this;
}

template<typename T, size_t size_>
inline typename static_array<T, size_>::iterator& static_array<T, size_>::iterator::operator--()
{
    if (this->index == 0)
    {
        throw std::range_error("cannot decrement begin iterator");
    }

    do
    {
        this->index--;
    } while (this->index > 0 && !this->container->valid(this->index));
    return *this;
}

#endif