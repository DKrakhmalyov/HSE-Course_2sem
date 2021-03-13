#include "node.h"

template<typename T>
Node<T>::Node() noexcept {
    this->id = minAvailableId++;
}

template<typename T>
Node<T>::~Node() noexcept = default;

template<typename T>
int32_t Node<T>::getIndex() const noexcept {
    return this->id;
}