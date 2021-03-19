
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"

template <typename T = void>
class PtrsGraph : public IPtrsGraph<T>
{
public:
    PtrsGraph(){};

    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&weight)
    {
        if (from->empty())
            verticesCount++;

        if (to->empty())
            verticesCount++;

        from->addEgde(to, std::forward<T>(weight));
    };

    virtual int VerticesCount() const
    {
        return verticesCount;
    };

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const
    {
        for (auto nextVertex : vertex->getNextVertices())
            vertices.push_back(nextVertex.first);
    };

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const
    {
        for (auto prevVertices : vertex->getPrevVertices())
            vertices.push_back(prevVertices.first);
    };

private:
    int verticesCount = 0;
};

#endif //HOMEWORK_1_PTRSGRAPH_H
