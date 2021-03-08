
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"
#include <unordered_set>
#include <queue>

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {

public:
    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj);

    PtrsGraph() = default;

    [[nodiscard]] virtual int VerticesCount() const;

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const;

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const;

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const;

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const;
protected:
    std::unordered_set<Node<T>*> _vertices;
    void _dfs(Node<T> *vertex, std::unordered_set<Node<T> *> &used, std::vector<Node<T> *> &vertices);
};

#endif //HOMEWORK_1_PTRSGRAPH_H
