#include "arcGraph.h"

template<typename T>
ArcGraph<T>& ArcGraph<T>::operator=(const ArcGraph<T> &other) {
    if (&other == this)
        return *this;

    m_graph = other.m_graph;
    m_vtx2idx = other.m_vtx2idx;
    m_idx2vtx = other.m_idx2vtx;
    return *this;
}

template<typename T>
ArcGraph<T>& ArcGraph<T>::operator=(ArcGraph<T> &&other) {
    if (&other == this)
        return *this;

    m_graph = std::move(other.m_graph);
    m_vtx2idx = std::move(other.m_vtx2idx);
    m_idx2vtx = std::move(other.m_idx2vtx);
    return *this;
}

template<typename T>
ArcGraph<T>::ArcGraph(IGraph<T> *_oth) {
    std::vector<std::pair<T, std::pair<int, int>>> arcGraph;
    _oth->TransformToArc(arcGraph);
    ArcGraph<T>::ConstructFromArc(arcGraph);
}

template<typename T>
int ArcGraph<T>::VerticesCount() const {
    return static_cast<int>(m_idx2vtx.size());
}

template<typename T>
void ArcGraph<T>::AddEdge(int from, int to, T &&element) {
    if (ArcGraph<T>::CheckEdge(from, to))
        return;

    if (m_vtx2idx.find(from) == m_vtx2idx.end())
        ArcGraph<T>::AddVertex(from);

    if (m_vtx2idx.find(to) == m_vtx2idx.end())
        ArcGraph<T>::AddVertex(to);

    m_graph.push_back(std::make_pair(element, std::make_pair(from, to)));
}

template<typename T>
void ArcGraph<T>::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    for (const std::pair<T, std::pair<int, int>> &i : m_graph)
        if (i.second.first == vertex)
            vertices.push_back(i.second.second);
}


template<typename T>
void ArcGraph<T>::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    for (const std::pair<T, std::pair<int, int>> &i : m_graph)
        if (i.second.second == vertex)
            vertices.push_back(i.second.first);
}

template<typename T> 
void ArcGraph<T>::DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
    if (m_vtx2idx.find(vertex) == m_vtx2idx.end())
        return;

    std::vector<bool> used(ArcGraph<T>::VerticesCount(), false);
    ArcGraph<T>::DoDFS(vertex, vertices, used);
}

template<typename T>
void ArcGraph<T>::BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
    if (m_vtx2idx.find(vertex) == m_vtx2idx.end())
        return;

    std::vector<bool> used(ArcGraph<T>::VerticesCount(), false);
    ArcGraph<T>::DoBFS(vertex, vertices, used);
}

template<typename T>
void ArcGraph<T>::AddVertex(int vertex) {
    if (m_vtx2idx.find(vertex) != m_vtx2idx.end())
        return;

    m_vtx2idx[vertex] = m_vtx2idx.size();    
    m_idx2vtx.push_back(vertex);
}

template<typename T> 
bool ArcGraph<T>::CheckEdge(int from, int to) const {
    for (const std::pair<T, std::pair<int, int>> &i : m_graph)
        if (i.second.first == from && i.second.second == to)
            return true;
    return false;
}

template<typename T>
void ArcGraph<T>::TransformToArc(std::vector<std::pair<T, std::pair<int, int>>> &graph) const {
    graph = m_graph;
}

template<typename T>
void ArcGraph<T>::ConstructFromArc(std::vector<std::pair<T, std::pair<int, int>>> &graph) {
    for (std::pair<T, std::pair<int, int>> &arc : graph)
        ArcGraph<T>::AddEdge(arc.second.first, arc.second.second, std::move(arc.first));
}

template<typename T>
void ArcGraph<T>::DoDFS(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const {
    used[m_vtx2idx.at(vertex)] = true;
    vertices.push_back(vertex);

    for (const std::pair<T, std::pair<int, int>> &v : m_graph)
        if (v.second.first == vertex && !used[m_vtx2idx.at(v.second.second)])
            ArcGraph<T>::DoDFS(v.second.second, vertices, used);
}

template<typename T>
void ArcGraph<T>::DoBFS(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const {
    used[m_vtx2idx.at(vertex)] = true;

    std::queue<int> q;
    q.push(vertex);

    while (q.size()) {
        int current_vertex = q.front();
        vertices.push_back(current_vertex);
        q.pop();

        for (const std::pair<T, std::pair<int, int>> &v : m_graph)
            if (v.second.first == current_vertex && !used[m_vtx2idx.at(v.second.second)]) {
                used[m_vtx2idx.at(v.second.second)] = true;
                q.push(v.second.second);
            }
    }
}