#include "nodePair.h"

template<typename T>
NodePair<T>::NodePair() noexcept {
    this->edge = std::pair<int32_t, int32_t>(-1, -1);
    this->weight = nullptr;
}

template<typename T>
NodePair<T>::NodePair(int32_t firstNode, int32_t secondNode, const T& weght) noexcept {
    T* _weight = new T(weght);
    this->edge = std::pair<int32_t, int32_t>(firstNode, secondNode);
    this->weight = _weight;
}

template<typename T>
NodePair<T>::NodePair(const NodePair& pair) noexcept {
    if (pair.valueIsEmpty()) {
        return;
    }
    this->edge.first = pair.getFirstNode();
    this->edge.second = pair.getSecondNode();
    this->weight = new T(*pair.weight);
}

template<typename T>
NodePair<T>::~NodePair() noexcept {
    if (this->valueIsNotEmpty()) {
        this->clearValue();
    }
}

template<typename T>
int32_t NodePair<T>::getFirstNode() const {
    if (this->valueIsEmpty()) {
        throw std::invalid_argument("Can't get Node from empty pair!");
    }
    return this->edge.first;
}

template<typename T>
int32_t NodePair<T>::getSecondNode() const {
    if (this->valueIsEmpty()) {
        throw std::invalid_argument("Can't get Node from empty pair!");
    }
    return this->edge.second;
}

template<typename T>
NodePair<T>& NodePair<T>::operator = (const NodePair<T>& other) noexcept {
    if (this == &other) {
        return *this;
    }
    if (this->valueIsNotEmpty()) {
        this->clearValue();
    }
    if (other.valueIsEmpty()) {
        return *this;
    }
    this->edge.first = other.edge.first;
    this->edge.second = other.edge.second;
    this->weight = new T(*other.weight);
}

template<typename T>
bool NodePair<T>::valueIsEmpty() const noexcept {
    return this->weight == nullptr || this->edge.first == -1 || this->edge.second == -1;
}

template<typename T>
bool NodePair<T>::valueIsNotEmpty() const noexcept {
    return !this->valueIsEmpty();
}

template<typename T>
void NodePair<T>::clearValue() noexcept {
    if (this->weight != nullptr) {
        delete this->weight;
    }
    this->edge.first = -1;
    this->edge.second = -1;
}

template<typename T>
T NodePair<T>::getWeight() const {
    if (this->weight == nullptr) {
        throw std::invalid_argument("Can't get weight from empty node pair!");
    }
    return *this->weight;
}