
#ifndef HOMEWORK_1_NODE_H
#define HOMEWORK_1_NODE_H

template<typename T>
struct PtrsEdge;

template<typename T>
class Node {
public:
    std::vector<PtrsEdge<T>> next;
    std::vector<PtrsEdge<T>> prev;
};

template<typename T>
struct PtrsEdge {
    Node<T> *from;
    Node<T> *to;
    T &&element;

    PtrsEdge() = default;

    PtrsEdge(Node<T> *_from, Node<T> *_to, T &&_element) :
        from(_from),
        to(_to),
        element(std::move(_element)) {
    }

    PtrsEdge(const PtrsEdge<T> &edge) : 
        from(edge.from),
        to(edge.to),
        element(std::move(edge.element)) {
    }

    PtrsEdge<T> operator= (const PtrsEdge<T> &edge) {
        from = edge.from;
        to = edge.to;
        element = std::move(edge.element);
        return *this;
    }
};

#endif //HOMEWORK_1_NODE_H
