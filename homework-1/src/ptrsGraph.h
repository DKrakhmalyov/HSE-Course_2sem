
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"

template <typename T = void>
class PtrsGraph : public IPtrsGraph<T>
{
private:
    std::vector<Node<T> *> ptrs;

public:
    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj)
    {
        bool ok1 = true, ok2 = true;
        for (auto x: ptrs) {
            if (x->_id == from->_id) {
                ok1 = false;
            }
            if (x->_id == to->_id) {
                ok2 = false;
            }
        }
        if (ok1) {
            ptrs.push_back(from);
        }
        if (ok2) {
            ptrs.push_back(to);
        }
        from->addVert(to, std::move(_obj));
    };

    PtrsGraph(){};
    virtual ~PtrsGraph()
    {
        for (auto node : ptrs)
        {
            delete node;
            node = nullptr;
        }
    }
    virtual int VerticesCount() const { return ptrs.size(); };

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const
    {
        vertices = vertex->getVerts();
    };

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const
    {
        for (auto point : ptrs)
        {
            for (auto x : point->getVerts())
            {
                if (x == vertex)
                {
                    vertices.push_back(point);
                }
            }
        }
    };

};

#endif //HOMEWORK_1_PTRSGRAPH_H
