//
// Created by Андрей Москалёв on 08.03.2021.
//

#include "listGraph.h"

template<typename T>
int ListGraph<T>::VerticesCount() const {
    return _g.size();
}

template<typename T>
void ListGraph<T>::AddEdge(int from, int to, T &&element) {
    _g[from].push_back({to, element});
    _gt[to].push_back({from, element});
}

template<typename T>
void ListGraph<T>::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    assert(vertex < _g.size());
    vertices = _g[vertex];
}

template<typename T>
void ListGraph<T>::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    assert(vertex < _g.size());
    vertices = _gt[vertex];
}

template<typename T>
void ListGraph<T>::DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
    assert(vertex < _g.size());
    std::unordered_set<int> used;
    _dfs(vertex, used, vertices);
}

template<typename T>
void ListGraph<T>::_dfs(int vertex, std::unordered_set<int> used, std::vector<int> &vertices) const {
    used.insert(vertex);
    vertices.push_back(vertex);
    for (int to : _g[vertex]) {
        if (!used.contains(to)) {
            _dfs(to, used, vertices);
        }
    }
}

template<typename T>
void ListGraph<T>::BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
    assert(vertex < _g.size());
    std::queue<int> q;
    q.push(vertex);
    std::unordered_set<int> used;
    while (!q.empty()) {
        int cur_vertex = q.front();
        q.pop();
        for (int to : _g[cur_vertex]) {
            if (!used.contains(to)) {
                vertices.push_back(cur_vertex);
                used.insert(cur_vertex);
            }
        }
    }
}
