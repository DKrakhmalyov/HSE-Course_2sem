
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {
    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) {};

    virtual int VerticesCount() const {return 0;};

    virtual void GetNextVertices(int vertex, std::vector<Node<T> *> &vertices) const {};

    virtual void GetPrevVertices(int vertex, std::vector<Node<T> *> &vertices) const {};

    virtual void DeepFirstSearch(int vertex, std::vector<Node<T> *> &vertices) const {};

    virtual void BreadthFirstSearch(int vertex, std::vector<Node<T> *> &vertices) const {};
};

#endif //HOMEWORK_1_PTRSGRAPH_H
