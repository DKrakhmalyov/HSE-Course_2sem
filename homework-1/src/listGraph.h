
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <cassert>
#include <algorithm>


template<typename T>
class ListGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element);

    ListGraph() = default;

    ListGraph(IGraph<T> *_oth);

    [[nodiscard]] virtual int VerticesCount() const;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const;

    virtual void GetEdges(std::vector<std::tuple<int, int, T>> &edges) const;

    virtual void GetVertices(std::vector<int> &vertices) const;

    virtual T GetEdgeWeight(int vertex_u, int vertex_v) const;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const;

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const;
protected:
    std::map<int, std::vector<std::pair<int, T>>> _g;
    void _dfs(int vertex, std::unordered_set<int> &used, std::vector<int> &vertices) const;
};

template<typename T>
int ListGraph<T>::VerticesCount() const {
    return _g.size();
}

template<typename T>
void ListGraph<T>::AddEdge(int from, int to, T &&element) {
    bool exist = false;
    for (const auto &now : _g[from]) {
        if (now.first == to) {
            exist = true;
            break;
        }
    }
    // кратные ребра не поддерживаются, т.к. это не мультиграф
    assert(!exist);

    _g[from].emplace_back(to, element);
}

template<typename T>
void ListGraph<T>::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    // нельзя получить список выходящих ребер несуществующей вершины
    assert(_g.contains(vertex));

    for (auto to : _g.find(vertex)->second) {
        vertices.push_back(to.first);
    }
}

template<typename T>
void ListGraph<T>::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    // нельзя получить список входящих ребер несуществующей вершины
    assert(_g.contains(vertex));

    for (auto now : _g) {
        for (auto to : now.second) {
            if (to.first == vertex) {
                vertices.push_back(now.first);
            }
        }
    }
}

template<typename T>
void ListGraph<T>::DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
    // нельзя обходить граф от несуществующей вершины
    assert(_g.contains(vertex));

    std::unordered_set<int> used;
    _dfs(vertex, used, vertices);
}

template<typename T>
void ListGraph<T>::_dfs(int vertex, std::unordered_set<int> &used, std::vector<int> &vertices) const {
    used.insert(vertex);
    vertices.push_back(vertex);
    auto outgoing = _g.find(vertex);
    if (outgoing == _g.end()) {
        return;
    }
    for (auto to : outgoing->second) {
        if (!used.contains(to.first)) {
            _dfs(to.first, used, vertices);
        }
    }
}

template<typename T>
void ListGraph<T>::BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
    // нельзя обходить граф от несуществующей вершины
    assert(_g.contains(vertex));

    std::queue<int> q;
    q.push(vertex);
    std::unordered_set<int> used;
    while (!q.empty()) {
        int cur_vertex = q.front();
        vertices.push_back(cur_vertex);
        q.pop();
        auto outgoing = _g.find(cur_vertex);
        if (outgoing == _g.end()) {
            continue;
        }
        for (auto to : outgoing->second) {
            if (!used.contains(to.first)) {
                used.insert(to.first);
                q.push(to.first);
            }
        }
    }
}

template<typename T>
void ListGraph<T>::GetVertices(std::vector<int> &vertices) const {
    for (const auto& now : _g) {
        vertices.push_back(now.first);
    }
}

template<typename T>
T ListGraph<T>::GetEdgeWeight(int vertex_u, int vertex_v) const {
    auto it = _g.find(vertex_u);

    // нельзя получить вес ребра, которое не существует
    assert(it != _g.end());

    for (auto to : it->second) {
        if (to.first == vertex_v) {
            return to.second;
        }
    }
    // нельзя получить вес ребра, которое не существует
    assert(false);
}

template<typename T>
void ListGraph<T>::GetEdges(std::vector<std::tuple<int, int, T>> &edges) const {
    for (const auto& from : _g) {
        for (auto to : from.second) {
            edges.emplace_back(from.first, to.first, to.second);
        }
    }
}

template<typename T>
ListGraph<T>::ListGraph(IGraph<T> *_oth) {
    std::vector<std::tuple<int, int, T>> edges;
    _oth->GetEdges(edges);
    for (auto edge : edges) {
        AddEdge(get<0>(edge), get<1>(edge), std::move(get<2>(edge)));
    }
}

#endif //HOMEWORK_1_LISTGRAPH_H
