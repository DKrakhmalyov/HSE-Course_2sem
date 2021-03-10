
#ifndef HOMEWORK_1_ARCGRAPH_H
#define HOMEWORK_1_ARCGRAPH_H

#include "../graph.h"
#include <unordered_set>
#include <utility>
#include <cassert>
#include <unordered_set>
#include <queue>
#include <tuple>
#include <vector>

template<typename T = void>
class ArcGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element);

    ArcGraph() = default;

    ArcGraph(IGraph<T> *_oth) {};

    [[nodiscard]] virtual int VerticesCount() const;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const;

    virtual void GetEdges(std::vector<std::tuple<int, int, T>> &edges) const;

    virtual void GetVertices(std::vector<int> &vertices) const;

    virtual T GetEdgeWeight(int from, int to) const;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const;

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const;
protected:
    std::unordered_set<int> _vertices;
    std::vector<std::tuple<int, int, T>> _g;
    void _dfs(int vertex, std::unordered_set<int> &used, std::vector<int> &vertices) const;
};

template<typename T>
int ArcGraph<T>::VerticesCount() const {
    return _vertices.size();
}

template<typename T>
void ArcGraph<T>::AddEdge(int from, int to, T &&element) {
    _vertices.insert(from);
    _vertices.insert(to);

    bool exist = false;
    for (const auto &now : _g) {
        if (get<0>(now) == from && get<1>(now) == to) {
            exist = true;
        }
    }

    // кратные ребра не поддерживаются, т.к. это не мультиграф
    assert(!exist);
    _g.emplace_back(from, to, element);
}

template<typename T>
void ArcGraph<T>::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    // нельзя получить список выходящих ребер несуществующей вершины
    assert(_vertices.contains(vertex));

    for (auto edge : _g) {
        if (get<0>(edge) == vertex) {
            vertices.push_back(get<1>(edge));
        }
    }
}

template<typename T>
void ArcGraph<T>::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    // нельзя получить список входящих ребер несуществующей вершины
    assert(_vertices.contains(vertex));

    for (auto edge : _g) {
        if (get<1>(edge) == vertex) {
            vertices.push_back(get<0>(edge));
        }
    }
}

template<typename T>
void ArcGraph<T>::DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
    // нельзя обходить граф от несуществующей вершины
    assert(_vertices.contains(vertex));

    std::unordered_set<int> used;
    _dfs(vertex, used, vertices);
}

template<typename T>
void ArcGraph<T>::_dfs(int vertex, std::unordered_set<int> &used, std::vector<int> &vertices) const {
    used.insert(vertex);
    vertices.push_back(vertex);
    std::vector<int> neighbours;
    GetNextVertices(vertex, neighbours);
    for (int to : neighbours) {
        if (!used.contains(to)) {
            _dfs(to, used, vertices);
        }
    }
}

template<typename T>
void ArcGraph<T>::BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
    // нельзя обходить граф от несуществующей вершины
    assert(_vertices.contains(vertex));

    std::queue<int> q;
    q.push(vertex);
    std::unordered_set<int> used;
    while (!q.empty()) {
        int cur_vertex = q.front();
        vertices.push_back(cur_vertex);
        q.pop();
        std::vector<int> neighbours;
        GetNextVertices(vertex, neighbours);
        for (int to : neighbours) {
            if (!used.contains(to)) {
                used.insert(to);
                q.push(to);
            }
        }
    }
}

template<typename T>
void ArcGraph<T>::GetVertices(std::vector<int> &vertices) const {
    for (const auto &now : _vertices) {
        vertices.push_back(now);
    }
}

template<typename T>
void ArcGraph<T>::GetEdges(std::vector<std::tuple<int, int, T>> &edges) const {
    edges = _g;
}

template<typename T>
T ArcGraph<T>::GetEdgeWeight(int from, int to) const {
    for (const auto &edge : _g) {
        if (get<0>(edge) == from && get<1>(edge) == to) {
            return get<2>(edge);
        }
    }
}

#endif //HOMEWORK_1_ARCGRAPH_H
