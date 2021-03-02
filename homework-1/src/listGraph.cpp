#include "listGraph.h"

#include <iostream>

template <typename T>
void ListGraph<T>::GetVertices(std::vector<int> &vertices) const {
    for (const std::pair<int, std::vector<std::pair<int, T>>> & i : m_graph)
        vertices.push_back(i.first);
}

template <typename T>
void ListGraph<T>::ConstructFromArc(std::vector<std::pair<T, std::pair<int, int>>> &graph) {
    for (std::pair<T, std::pair<int, int>> arc : graph)
        ListGraph<T>::AddEdge(arc.second.first, arc.second.second, std::move(arc.first));
}

template <typename T> 
void ListGraph<T>::TransformToArc(std::vector<std::pair<T, std::pair<int, int>>> &graph) const {
    std::vector<int> vertices;
    ListGraph<T>::GetVertices(vertices);

    for (const int & vertex : vertices)
        for (const std::pair<int, T> & to : m_graph.at(vertex))
            graph.push_back(std::make_pair(to.second, std::make_pair(vertex, to.first)));
}

template <typename T>
ListGraph<T>::ListGraph(IGraph<T> *_oth) {
    std::vector<std::pair<T, std::pair<int, int>>> arcGraph;
    _oth->TransformToArc(arcGraph);
    ListGraph<T>::ConstructFromArc(arcGraph);
}

template <typename T>
void ListGraph<T>::AddEdge(int from, int to, T&& elem) {    
    if (ListGraph<T>::CheckEdge(from, to))
        return;

    if (m_graph.find(to) == m_graph.end())
        m_graph[to] = std::vector <std::pair <int, T>>();
    
    if (m_reversed_graph.find(to) == m_reversed_graph.end())
        m_reversed_graph[from] = std::vector <std::pair <int, T>>();
    
    m_graph[from].emplace_back(to, elem);
    m_reversed_graph[to].emplace_back(from, elem);
}

template <typename T>
int ListGraph<T>::VerticesCount() const {
    return static_cast<int>(m_graph.size());
}

template <typename T>
bool ListGraph<T>::CheckEdge(int from, int to) const {
    if (m_graph.find(from) == m_graph.end())
        return false;

    bool hasEdge = 0;
    for (const std::pair<int, T> & i : m_graph.at(from))
        hasEdge |= bool(i.first == to);
    return hasEdge;
}

template <typename T>
void ListGraph<T>::GetNextVertices(int vertex, std::vector<int>& vertices) const {
    if (m_graph.find(vertex) == m_graph.end())
        return;

    for (const std::pair<int, T> & v : m_graph.at(vertex))
        vertices.push_back(v.first);
}

template <typename T>
void ListGraph<T>::GetPrevVertices(int vertex, std::vector<int>& vertices) const {
    if (m_reversed_graph.find(vertex) == m_reversed_graph.end())
        return;

    for (const std::pair<int, T> & v : m_reversed_graph.at(vertex))
        vertices.push_back(v.first);
}

template <typename T>
void ListGraph<T>::DoDFS(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const {
    used[vertex] = true;
    vertices.push_back(vertex);

    for (const std::pair<int, T> &next : m_graph.at(vertex))
        if (!used[next.first])
            DoDFS(next.first, vertices, used);
}

template <typename T>
void ListGraph<T>::DeepFirstSearch(int vertex, std::vector<int>& vertices) const {
    std::vector <bool> used(ListGraph<T>::VerticesCount(), false);
    ListGraph<T>::DoDFS(vertex, vertices, used);
}

template<typename T>
void ListGraph<T>::DoBFS(int vertex, std::vector<int> &vertices, std::vector <bool> &used) const {
    used[vertex] = true;

    std::queue<int> q;
    q.push(vertex);

    while (q.size()) {
        int current_vertex = q.front();
        vertices.push_back(current_vertex);
        q.pop();

        for (const std::pair<int, T> &next : m_graph.at(current_vertex))
            if (!used[next.first]) {
                q.push(next.first);
                used[next.first] = true;
            }
    }
}

template <typename T>
void ListGraph<T>::BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
    std::vector <bool> used(ListGraph<T>::VerticesCount(), false);
    ListGraph<T>::DoBFS(vertex, vertices, used);
}
