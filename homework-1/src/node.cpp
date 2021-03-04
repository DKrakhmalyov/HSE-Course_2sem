#include "node.h"

template <typename T> 
int Node<T>::count = 0;

template <typename T>
Node<T>::Node() {
    number = Node<T>::count++;
}

template <typename T>
void Node<T>::Mark() {
    used = true;
}

template <typename T>
void Node<T>::Unmark() {
    used = false;
}

template <typename T> 
bool Node<T>::Marked() const {
    return used;
}

template <typename T>
bool Node<T>::CheckEdgeTo(Node<T> *vertex) const {
    for (const std::pair<Node<T>*, T> &node : next)
        if (node.first == vertex)
            return true;
    return false;  
}

template <typename T>
void Node<T>::AddNextVertex(Node<T> *vertex, T &&element) {
    if (Node<T>::CheckEdgeTo(vertex))
        return;

    next.emplace_back(vertex, element);
}

template <typename T>
void Node<T>::GetNextVertices(std::vector<Node<T> *> &vertices) const {
    for (const std::pair<Node<T>*, T> &node : next)
        vertices.push_back(node.first);
}

template <typename T>
bool Node<T>::less::operator() (Node<T> *l, Node<T> *r) const {
    return l->number < r->number;
}