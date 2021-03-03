#ifndef HOMEWORK_1_GRAPH_H
#define HOMEWORK_1_GRAPH_H

#include <queue>
#include <vector>
#include <unordered_map>
#include "src/node.h"

template<typename T>
class IGraph {

public:

    virtual ~IGraph() = default;

    virtual int VerticesCount() const = 0;

    virtual void AddEdge(int from, int to, T &&_obj) = 0;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const = 0;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const = 0;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const = 0;

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const = 0;

    virtual void TransformToArc(std::vector<std::pair<T, std::pair<int, int>>> &graph) const = 0;

private:

    virtual bool CheckEdge(int from, int to) const = 0;

    virtual void DoDFS(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const = 0;

    virtual void DoBFS(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const = 0;

    virtual void ConstructFromArc(std::vector<std::pair<T, std::pair<int, int>>> &graph) = 0;
};

template<typename T = void>
class IPtrsGraph {
public:
    virtual ~IPtrsGraph();

    IPtrsGraph();

    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) = 0;

    virtual int VerticesCount() const = 0;

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;
};

#endif //HOMEWORK_1_GRAPH_H
