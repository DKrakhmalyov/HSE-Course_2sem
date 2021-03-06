
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
        nodes.insert(from);
        nodes.insert(to);
        from->addEgde(to, std::move(weight));
    };

    virtual int VerticesCount() const
    {
        return nodes.size();
    };

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const
    {
        vertices = vertex->getEdges();
    };

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const
    {
        for (auto node : nodes)
            for (auto edge : node->getEdges())
                if (edge == vertex)
                    vertices.push_back(node);
    };

private:
    std::unordered_set<Node<T> *> nodes;
};

#endif //HOMEWORK_1_PTRSGRAPH_H
