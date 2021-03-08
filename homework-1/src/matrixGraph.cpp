//
// Created by Андрей Москалёв on 08.03.2021.
//
#include "matrixGraph.h"

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
        _gt.resize(need_size);
        for (size_t i = 0; i < need_size; ++i) {
            _g[i].resize(need_size);
            _gt[i].resize(need_size);
        }
    }
    _g[from][to].first = true;
    _g[from][to].second = element;
    _gt[to][from].first = true;
    _gt[to][from].second = element;
}
template<typename T>
void MatrixGraph<T>::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    assert(_vertices.contains(vertex));
    for (int to : _vertices) {
        if (_g[vertex][to].first) {
            vertices.push_back(to);
        }
    }
}

template<typename T>
void MatrixGraph<T>::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    assert(_vertices.contains(vertex));
    for (int to : _vertices) {
        if (_gt[vertex][to].first) {
            vertices.push_back(to);
        }
    }
}

template<typename T>
void MatrixGraph<T>::DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
    assert(_vertices.contains(vertex));
    std::unordered_set<int> used;
    _dfs(vertex, used, vertices);
}

template<typename T>
void MatrixGraph<T>::_dfs(int vertex, std::unordered_set<int> used, std::vector<int> &vertices) const {
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
    assert(_vertices.contains(vertex));
    std::queue<int> q;
    q.push(vertex);
    std::unordered_set<int> used;
    while (!q.empty()) {
        int cur_vertex = q.front();
        q.pop();
        for (int to : _vertices) {
            if (_g[vertex][to].first && !used.contains(to)) {
                vertices.push_back(cur_vertex);
                used.insert(cur_vertex);
            }
        }
    }
}
