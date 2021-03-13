//
// Created by dikson on 02.03.2021.
//

#ifndef HOMEWORK_1_GRAPH_H
#define HOMEWORK_1_GRAPH_H

#include <vector>
#include "src/node.h"
#include <queue>

template<typename T>
class IGraph {
public:

    virtual ~IGraph() {}

    IGraph() {};

    IGraph(IGraph *_oth) {
        _oth->Convert(this);
    };

    virtual void AddEdge(int from, int to, T &&_obj) = 0;

    virtual int VerticesCount() const = 0;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const = 0;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const = 0;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const = 0;

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const = 0;

    virtual void Convert(IGraph<T> *Gr) {};
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

    virtual void Convert(IGraph<T> *Gr) {};

};

#endif //HOMEWORK_1_GRAPH_H
