//
// Created by Андрей Москалёв on 08.03.2021.
//

#include "ptrsGraph.h"

template<typename T>
int PtrsGraph<T>::VerticesCount() const {
    return _vertices.size();
}

template<typename T>
void PtrsGraph<T>::AddEdge(Node<T> *from, Node<T> *to, T &&_obj) {
    _vertices.insert(from);
    _vertices.insert(to);
    from->outgoing.push_back({to, _obj});
    to->incoming.push_back({from, _obj});
}

template<typename T>
void PtrsGraph<T>::GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
    assert(_vertices.contains(vertex));
    vertices = vertex->outgoing;
}

template<typename T>
void PtrsGraph<T>::GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
    assert(_vertices.contains(vertex));
    vertices = vertex->incoming;
}

template<typename T>
void PtrsGraph<T>::DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
    assert(_vertices.contains(vertex));
    std::unordered_set<Node<T>*> used;
    _dfs(vertex, used, vertices);
}

template<typename T>
void PtrsGraph<T>::_dfs(Node<T> *vertex, std::unordered_set<Node<T> *> &used, std::vector<Node<T> *> &vertices) {
    used.insert(vertex);
    vertices.push_back(vertex);
    for (int to : vertex->outgoing) {
        if (!used.contains(to)) {
            _dfs(to, used, vertices);
        }
    }
}

template<typename T>
void PtrsGraph<T>::BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
    assert(_vertices.contains(vertex));
    std::queue<Node<T> *> q;
    q.push(vertex);
    std::unordered_set<int> used;
    while (!q.empty()) {
        Node<T> *cur_vertex = q.front();
        q.pop();
        for (int to : cur_vertex->outgoing) {
            if (!used.contains(to)) {
                vertices.push_back(cur_vertex);
                used.insert(cur_vertex);
            }
        }
    }
}


