#pragma once

#include <vector>
#include <utility>

#include "src/nodePair.h"
#include "src/node.h"

template<typename T = void>
class IGraph {
public:
    virtual ~IGraph() {}

    IGraph() {};

    IGraph(IGraph* other) {};

    virtual void addEdge(const int32_t& from, const int32_t& to, T _obj) = 0;

    virtual int verticesCount() = 0;

    virtual void getNextVertices(const int32_t& vertex, std::vector<int32_t> &vertices) = 0;

    virtual void getPrevVertices(const int32_t& vertex, std::vector<int32_t> &vertices) = 0;

    virtual void deepFirstSearch(const int32_t& vertex, std::vector<int32_t> &vertices) = 0;

    virtual void breadthFirstSearch(const int32_t& vertex, std::vector<int32_t> &vertices) = 0;

};

template<typename T = void>
class IPtrsGraph {
public:
    virtual ~IPtrsGraph() {}

    IPtrsGraph() {};

    virtual void addEdge(Node<T> *from, Node<T> *to, const T &_obj) = 0;

    virtual int verticesCount() = 0;

    virtual void getNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) = 0;

    virtual void getPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) = 0;

    virtual void deepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) = 0;

    virtual void breadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) = 0;
};
