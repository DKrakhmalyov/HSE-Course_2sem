#include "listGraph.h"

template<typename T>
ListGraph<T>& ListGraph<T>::operator=(const ListGraph<T> &other) {
    if (&other == this)
        return *this;

    m_graph = other.m_graph;
    m_idx2vtx = other.m_idx2vtx;
    m_vtx2idx = other.m_vtx2idx;
    m_reversed_graph = other.m_reversed_graph;
    return *this;
}

template<typename T>
ListGraph<T>& ListGraph<T>::operator=(ListGraph<T> &&other) {
    if (&other == this)
        return *this;

    m_graph = std::move(other.m_graph);
    m_idx2vtx = std::move(other.m_idx2vtx);
    m_vtx2idx = std::move(other.m_vtx2idx);
    m_reversed_graph = std::move(other.m_reversed_graph);
    return *this;
}

template<typename T>
ListGraph<T>::ListGraph(IGraph<T> *_oth) {
    std::vector<std::pair<T, std::pair<int, int>>> arcGraph;
    _oth->TransformToArc(arcGraph);
    ListGraph<T>::ConstructFromArc(arcGraph);
}

template<typename T>
int ListGraph<T>::VerticesCount() const {
    return static_cast<int>(m_idx2vtx.size());
}

template<typename T>
void ListGraph<T>::AddEdge(int from, int to, T &&elem) {    
    if (m_vtx2idx.find(from) == m_vtx2idx.end())
        ListGraph<T>::AddVertex(from);

    if (m_vtx2idx.find(to) == m_vtx2idx.end())
        ListGraph<T>::AddVertex(to);

    if (ListGraph<T>::CheckEdge(m_vtx2idx.at(from), m_vtx2idx.at(to)))
        return;
        
    m_graph[m_vtx2idx.at(from)].emplace_back(m_vtx2idx.at(to), elem);
    m_reversed_graph[m_vtx2idx.at(to)].emplace_back(m_vtx2idx.at(from), elem);
}

template<typename T>
void ListGraph<T>::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    if (m_vtx2idx.find(vertex) == m_vtx2idx.end())
        return;

    for (const std::pair<int, T> &i : m_graph[m_vtx2idx.at(vertex)])
        vertices.push_back(m_idx2vtx[i.first]);
}

template<typename T>
void ListGraph<T>::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    if (m_vtx2idx.find(vertex) == m_vtx2idx.end())
        return;

    for (const std::pair<int, T> &i : m_reversed_graph[m_vtx2idx.at(vertex)])
        vertices.push_back(m_idx2vtx[i.first]);
}

template<typename T>
void ListGraph<T>::DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
    if (m_vtx2idx.find(vertex) == m_vtx2idx.end())
        return;

    std::vector <bool> used(ListGraph<T>::VerticesCount(), false);
    ListGraph<T>::DoDFS(m_vtx2idx.at(vertex), vertices, used);
}

template<typename T>
void ListGraph<T>::BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
    if (m_vtx2idx.find(vertex) == m_vtx2idx.end())
        return;

    std::vector<bool> used(ListGraph<T>::VerticesCount(), false);
    ListGraph<T>::DoBFS(m_vtx2idx.at(vertex), vertices, used);
}

template<typename T>
void ListGraph<T>::AddVertex(int vertex) {
    if (m_vtx2idx.find(vertex) != m_vtx2idx.end())
        return;

    m_vtx2idx[vertex] = m_vtx2idx.size();
    m_idx2vtx.push_back(vertex);

    m_graph.push_back(std::vector<std::pair<int, T>>());
    m_reversed_graph.push_back(std::vector<std::pair<int, T>>());
}

template<typename T>
void ListGraph<T>::GetVertices(std::vector<int> &vertices) const {
    vertices = m_idx2vtx;
}

template<typename T>
bool ListGraph<T>::CheckEdge(int from, int to) const {
    bool hasEdge = false;
    for (const std::pair<int, T> & i : m_graph[from])
        hasEdge |= bool(i.first == to);
    return hasEdge;
}

template<typename T>
void ListGraph<T>::ConstructFromArc(std::vector<std::pair<T, std::pair<int, int>>> &graph) {
    for (std::pair<T, std::pair<int, int>> arc : graph)
        ListGraph<T>::AddEdge(arc.second.first, arc.second.second, std::move(arc.first));
}

template<typename T> 
void ListGraph<T>::TransformToArc(std::vector<std::pair<T, std::pair<int, int>>> &graph) const {
    std::vector<int> vertices;
    ListGraph<T>::GetVertices(vertices);

    for (const int & vertex : vertices)
        for (const std::pair<int, T> & to : m_graph[m_vtx2idx.at(vertex)])
            graph.push_back(std::make_pair(to.second, std::make_pair(vertex, m_idx2vtx[to.first])));
}

template<typename T>
void ListGraph<T>::DoDFS(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const {
    used[vertex] = true;
    vertices.push_back(m_idx2vtx[vertex]);

    for (const std::pair<int, T> &next : m_graph[vertex])
        if (!used[next.first])
            ListGraph<T>::DoDFS(next.first, vertices, used);
}

template<typename T>
void ListGraph<T>::DoBFS(int vertex, std::vector<int> &vertices, std::vector <bool> &used) const {
    used[vertex] = true;

    std::queue<int> q;
    q.push(vertex);

    while (q.size()) {
        int current_vertex = q.front();
        vertices.push_back(m_idx2vtx[current_vertex]);
        q.pop();

        for (const std::pair<int, T> &next : m_graph.at(current_vertex))
            if (!used[next.first]) {
                q.push(next.first);
                used[next.first] = true;
            }
    }
}