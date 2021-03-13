
#ifndef HOMEWORK_1_GRAPH_H
#define HOMEWORK_1_GRAPH_H

#include <vector>
#include <unordered_set>
#include <queue>
#include "src/node.h"

template<typename T>
class IGraph {
protected:
    void Construct(const IGraph & _oth) {
        std::vector<int> vertices;
        _oth.GetVertices(vertices);
        for (auto from : vertices) {
            std::vector<int> next_vertices;
            _oth.GetNextVertices(from, next_vertices);
            for (auto to : next_vertices) {
                AddEdge(from, to, _oth.GetEdgeWeight(from, to));
            }
        }
    }
public:
    virtual ~IGraph() {}

    IGraph() = default;

    IGraph(IGraph *_oth) {};

    virtual void AddEdge(int from, int to, T &&_obj) = 0;

    virtual int VerticesCount() const = 0;

    virtual void GetVertices(std::vector<int> &vertices) const = 0;

    virtual T GetEdgeWeight(int from, int to) const = 0;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const = 0;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const = 0;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::unordered_set<int> used;
        auto dfs = [this, &used, &vertices] (int vertex, auto const & dfs) {
            used.insert(vertex);
            vertices.push_back(vertex);
            std::vector<int> next_vertices;
            GetNextVertices(vertex, next_vertices);
            if (next_vertices.empty())
                return;
            for (auto i : next_vertices) {
                if (!used.contains(i))
                    dfs(i, dfs);
            }
        };
        dfs(vertex, dfs);
    };

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
        std::unordered_set<int> used;
        std::queue<int> queue;
        std::vector<int> next_vertices;
        queue.push(vertex);
        while (!queue.empty()) {
            int now = queue.front();
            vertices.push_back(now);
            queue.pop();
            next_vertices.clear();
            GetNextVertices(now, next_vertices);
            if (next_vertices.empty())
                continue;
            for (auto i : next_vertices) {
                if (!used.contains(i)) {
                    used.insert(i);
                    queue.push(i);
                }
            }
        }
    };
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
