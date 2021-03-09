
#ifndef HOMEWORK_1_GRAPH_H
#define HOMEWORK_1_GRAPH_H

#include <vector>
#include <list>
#include "src/node.h"

const int INF = 1e9;

template<typename T>
class IGraph {
public:
    virtual ~IGraph() {}

    IGraph() {};

    IGraph(IGraph *_oth) {};

    virtual void AddEdge(int from, int to, T &&_obj) = 0;

    virtual int VerticesCount() const = 0;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const = 0;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const = 0;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const = 0;

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const = 0;

    virtual std::list<std::pair<int, T>> __get__next__(int vertex) const = 0;
    
protected:
    virtual void __dfs__(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const = 0;
};

template<typename T = void>
class IPtrsGraph {
public:
    virtual ~IPtrsGraph() {}

    IPtrsGraph() {};

    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) = 0;

    virtual int VerticesCount() const = 0;

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;
};

#endif //HOMEWORK_1_GRAPH_H
