
#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H


#include "../graph.h"
#include <vector>
#include <unordered_set>
#include <cassert>
#include <queue>

template<typename T = void>
class MatrixGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element);

    MatrixGraph() = default;

    MatrixGraph(IGraph<T> *_oth);

    [[nodiscard]] virtual int VerticesCount() const;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const;

    virtual void GetEdges(std::vector<std::tuple<int, int, T>> &edges) const;

    virtual void GetVertices(std::vector<int> &vertices) const;

    virtual T GetEdgeWeight(int from, int to) const;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const;

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const;
protected:
    std::vector<std::vector<std::pair<bool, T>>> _g;

    std::unordered_set<int> _vertices;

    void _dfs(int vertex, std::unordered_set<int> &used, std::vector<int> &vertices) const;
};

template<typename T>
int MatrixGraph<T>::VerticesCount() const {
    return _vertices.size();
}
template<typename T>
void MatrixGraph<T>::AddEdge(int from, int to, T &&element) {
    _vertices.insert(from);
    _vertices.insert(to);
    if (int need_size = std::max(from, to); need_size >= _g.size()) {
        need_size += 1;
        _g.resize(need_size);
        for (size_t i = 0; i < need_size; ++i) {
            _g[i].resize(need_size, {false, T()});
        }
    }
    _g[from][to].first = true;
    _g[from][to].second = element;
}
template<typename T>
void MatrixGraph<T>::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    // нельзя получить список выходящих ребер несуществующей вершины
    assert(_vertices.contains(vertex));

    for (int to : _vertices) {
        if (_g[vertex][to].first) {
            vertices.push_back(to);
        }
    }
}

template<typename T>
void MatrixGraph<T>::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    // нельзя получить список входящих ребер несуществующей вершины
    assert(_vertices.contains(vertex));

    for (int from : _vertices) {
        if (_g[from][vertex].first) {
            vertices.push_back(from);
        }
    }
}

template<typename T>
void MatrixGraph<T>::DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
    // нельзя обходить граф от несуществующей вершины
    assert(_vertices.contains(vertex));

    std::unordered_set<int> used;
    _dfs(vertex, used, vertices);
}

template<typename T>
void MatrixGraph<T>::_dfs(int vertex, std::unordered_set<int> &used, std::vector<int> &vertices) const {
    used.insert(vertex);
    vertices.push_back(vertex);
    for (int to : _vertices) {
        if (_g[vertex][to].first && !used.contains(to)) {
            _dfs(to, used, vertices);
        }
    }
}

template<typename T>
void MatrixGraph<T>::BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
    // нельзя обходить граф от несуществующей вершины
    assert(_vertices.contains(vertex));

    std::queue<int> q;
    q.push(vertex);
    std::unordered_set<int> used;
    while (!q.empty()) {
        int cur_vertex = q.front();
        vertices.push_back(cur_vertex);
        q.pop();
        for (int to : _vertices) {
            if (_g[vertex][to].first && !used.contains(to)) {
                used.insert(to);
                q.push(to);
            }
        }
    }
}

template<typename T>
void MatrixGraph<T>::GetVertices(std::vector<int> &vertices) const {
    for (const auto &now : _vertices) {
        vertices.push_back(now);
    }
}
template<typename T>
T MatrixGraph<T>::GetEdgeWeight(int from, int to) const {
//    нельзя получить вес ребра, которое не существует
    assert(from >= 0 && from < _g.size() && to >= 0 && to < _g.size() && _g[from][to].first);

    return _g[from][to].second;
}

template<typename T>
void MatrixGraph<T>::GetEdges(std::vector<std::tuple<int, int, T>> &edges) const {
    for (const auto &from : _vertices) {
        for (const auto &to : _vertices) {
            if (_g[from][to].first) {
                edges.emplace_back(from, to, _g[from][to].second);
            }
        }
    }
}

template<typename T>
MatrixGraph<T>::MatrixGraph(IGraph<T> *_oth) {
    std::vector<std::tuple<int, int, T>> edges;
    _oth->GetEdges(edges);
    for (auto edge : edges) {
        AddEdge(get<0>(edge), get<1>(edge), std::move(get<2>(edge)));
    }
}

#endif //HOMEWORK_1_MATRIXGRAPH_H
