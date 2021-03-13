
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include <set>
#include "node.h"
#include "../graph.h"

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {

public:
    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) {
        from->nextVertexes.push_back(typename Node<T>::Edge(to, _obj));
        to->prevVertexes.push_back(typename Node<T>::Edge(from, _obj));
        graphVertices.insert(from);
        graphVertices.insert(to);
    };

    PtrsGraph() {};

    virtual int VerticesCount() const { return graphVertices.size(); };

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        for (auto [to, w] : vertex->nextVertexes) {
            vertices.push_back(to);
        }
    };

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        for (auto [from, w] : vertex->prevVertexes) {
            vertices.push_back(from);
        }
    };
private:
    std::set<Node<T>*> graphVertices;
};

#endif //HOMEWORK_1_PTRSGRAPH_H
