
#ifndef HOMEWORK_1_GRAPH_H
#define HOMEWORK_1_GRAPH_H

#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include "src/node.h"

template <typename T>
class IGraph
{
public:
    IGraph(){};

    IGraph(IGraph *_oth)
    {
        std::vector<std::pair<int, T>> edges;
        std::vector<T> weights;
        _oth->GetEdges(edges, weights);

        for (int i = 0; i < edges.size(); i++)
            AddEdge(edges[i].first, edges[i].second, weights[i]);
    };
    
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to, T &&_obj) = 0;

    virtual void GetEdges(std::vector<std::pair<int, int>> &edges, std::vector<T> &weights) const = 0;

    virtual int VerticesCount() const = 0;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const = 0;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const = 0;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const
    {
        std::unordered_set<int> usedVertices;
        RecursiveDfs(vertex, vertices, usedVertices);
    };

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const
    {
        std::queue<int> queue;
        std::unordered_set<int> usedVertices;

        queue.push(vertex);

        while (queue.size())
        {
            int currentVertex = queue.front();
            queue.pop();

            usedVertices.insert(currentVertex);
            vertices.push_back(currentVertex);

            std::vector<int> nextVertices;
            GetNextVertices(currentVertex, nextVertices);

            for (auto nextVertex : nextVertices)
                if (!usedVertices.contains(nextVertex))
                    queue.push(nextVertex);
        }
    };

private:
    virtual void RecursiveDfs(int vertex, std::vector<int> &vertices, std::unordered_set<int> &usedVertices) const
    {
        vertices.push_back(vertex);
        usedVertices.insert(vertex);

        std::vector<int> nextVertices;
        GetNextVertices(vertex, nextVertices);

        for (auto nextVertex : nextVertices)
            if (!usedVertices.contains(nextVertex))
                RecursiveDfs(nextVertex, vertices, usedVertices);
    };
};

template <typename T = void>
class IPtrsGraph
{
public:
    IPtrsGraph(){};

    virtual ~IPtrsGraph() {}

    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) = 0;

    virtual int VerticesCount() const = 0;

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const = 0;

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const
    {
        std::unordered_set<Node<T> *> usedVertices;
        RecursiveDfs(vertex, vertices, usedVertices);
    };

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const
    {
        std::queue<Node<T> *> queue;
        std::unordered_set<Node<T> *> usedVertices;

        queue.push(vertex);

        while (queue.size())
        {
            Node<T> *currentVertex = queue.front();
            queue.pop();

            usedVertices.insert(currentVertex);
            vertices.push_back(currentVertex);

            std::vector<Node<T> *> nextVertices;
            GetNextVertices(currentVertex, nextVertices);

            for (auto nextVertex : nextVertices)
                if (!usedVertices.contains(nextVertex))
                    queue.push(nextVertex);
        }
    };

private:
    virtual void RecursiveDfs(Node<T> *vertex, std::vector<Node<T> *> &vertices, std::unordered_set<Node<T> *> &usedVertices) const
    {
        vertices.push_back(vertex);
        usedVertices.insert(vertex);

        std::vector<Node<T> *> nextVertices;
        GetNextVertices(vertex, nextVertices);

        for (auto nextVertex : nextVertices)
            if (!usedVertices.contains(nextVertex))
                RecursiveDfs(nextVertex, vertices, usedVertices);
    };
};

#endif //HOMEWORK_1_GRAPH_H
