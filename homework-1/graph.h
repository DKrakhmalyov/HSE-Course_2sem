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

    IGraph(IGraph* _oth) {};

    virtual void AddEdge(int from, int to, T&& _obj) {};

    virtual int VerticesCount() const = 0;

    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) {};

    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) {};

    virtual void DeepFirstSearch(int vertex, std::vector<int>& vertices) {};

    virtual void BreadthFirstSearch(int vertex, std::vector<int>& vertices) {};

    virtual void CopyEdges(std::vector<std::pair<int, std::pair<int, T> > >& edges) {};
};

template<typename T = void>
class IPtrsGraph {
public:
    virtual ~IPtrsGraph() {}

    IPtrsGraph() {};

    virtual void AddEdge(Node<T>* from, Node<T>* to, T&& _obj) const = 0;

    virtual int VerticesCount() const = 0;

    virtual void GetNextVertices(Node<T>* vertex, std::vector<Node<T>*>& vertices) const = 0;

    virtual void GetPrevVertices(Node<T>* vertex, std::vector<Node<T>*>& vertices) const = 0;

    virtual void DeepFirstSearch(Node<T>* vertex, std::vector<Node<T>*>& vertices) const = 0;

    virtual void BreadthFirstSearch(Node<T>* vertex, std::vector<Node<T>*>& vertices) const = 0;

};

#endif //HOMEWORK_1_GRAPH_H
