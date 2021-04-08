
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

    virtual T GetEdgeWeight(Node<T> *from, Node<T> *to) const;

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const;

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const;
protected:
    int vertices_count = 0;
    void _dfs(Node<T> *vertex, std::unordered_set<Node<T> *> &used, std::vector<Node<T> *> &vertices) const;
};

template<typename T>
int PtrsGraph<T>::VerticesCount() const {
    return vertices_count;
}

template<typename T>
void PtrsGraph<T>::AddEdge(Node<T> *from, Node<T> *to, T &&_obj) {
    // нельзя добавлять ребра между несуществующими вершинами
    assert(from != nullptr && to != nullptr);

    if (!from->in_graph) {
        from->in_graph = true;
        vertices_count++;
    }
    if (!to->in_graph) {
        to->in_graph = true;
        vertices_count++;
    }
    from->outgoing.emplace_back(to, _obj);
    to->incoming.emplace_back(from, _obj);
}

template<typename T>
void PtrsGraph<T>::GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
    for (auto x : vertex->outgoing) {
        vertices.push_back(x.first);
    }
}

template<typename T>
void PtrsGraph<T>::GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
    for (auto x : vertex->incoming) {
        vertices.push_back(x.first);
    }
}

template<typename T>
void PtrsGraph<T>::DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
    std::unordered_set<Node<T>*> used;
    _dfs(vertex, used, vertices);
}

template<typename T>
void PtrsGraph<T>::_dfs(Node<T> *vertex, std::unordered_set<Node<T> *> &used, std::vector<Node<T> *> &vertices) const {
    used.insert(vertex);
    vertices.push_back(vertex);
    for (auto to : vertex->outgoing) {
        if (!used.contains(to.first)) {
            _dfs(to.first, used, vertices);
        }
    }
}

template<typename T>
void PtrsGraph<T>::BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
    std::queue<Node<T> *> q;
    q.push(vertex);
    std::unordered_set<Node<T> *> used;
    while (!q.empty()) {
        Node<T> *cur_vertex = q.front();
        q.pop();
        vertices.push_back(cur_vertex);
        for (auto to : cur_vertex->outgoing) {
            if (!used.contains(to.first)) {
                used.insert(to.first);
                q.push(to.first);
            }
        }
    }
}

template<typename T>
T PtrsGraph<T>::GetEdgeWeight(Node<T> *from, Node<T> *to) const {
    T weight = 0;
    for (auto now : from->outgoing) {
        if (now.first == to) {
            return now.second;
        }
    }
//    нельзя получить вес ребра, которое не существует
    assert(false);
}

#endif //HOMEWORK_1_PTRSGRAPH_H
