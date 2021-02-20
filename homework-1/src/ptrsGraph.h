
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {

public:
    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) {};

    PtrsGraph() {};

    virtual int VerticesCount() const { return 0; };

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {};

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {};

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {};

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {};
};

#endif //HOMEWORK_1_PTRSGRAPH_H
