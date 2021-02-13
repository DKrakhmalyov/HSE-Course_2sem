
#ifndef HOMEWORK_1_GRAPH_H
#define HOMEWORK_1_GRAPH_H

#include <vector>
#include "src/node.h"

template<typename T>
class IGraph {
public:
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to, T &&_obj) = 0;

    virtual int VerticesCount() const = 0;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const = 0;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const = 0;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const = 0;

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const = 0;
};

template<typename T>
class IPtrsGraph {
public:
    virtual ~IPtrsGraph() {}

    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) = 0;

    virtual int VerticesCount() const = 0;

    virtual void GetNextVertices(int vertex, std::vector<Node<T> *> &vertices) const = 0;

    virtual void GetPrevVertices(int vertex, std::vector<Node<T> *> &vertices) const = 0;

    virtual void DeepFirstSearch(int vertex, std::vector<Node<T> *> &vertices) const = 0;

    virtual void BreadthFirstSearch(int vertex, std::vector<Node<T> *> &vertices) const = 0;
};

#endif //HOMEWORK_1_GRAPH_H
