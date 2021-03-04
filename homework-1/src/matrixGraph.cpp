#include "matrixGraph.h"

template <typename T>
void MatrixGraph<T>::ResizeGraph(std::size_t new_size) {
    m_graph.resize(new_size);
    for (std::vector<std::pair<bool, T>> & i : m_graph)
        i.resize(new_size);
}

template <typename T>
void MatrixGraph<T>::AddVertex(int vertex) {
    if (m_vtx2idx.find(vertex) != m_vtx2idx.end())
        return;

    m_vtx2idx[vertex] = m_vtx2idx.size();
    m_idx2vtx.push_back(vertex);

    MatrixGraph<T>::ResizeGraph(MatrixGraph<T>::VerticesCount() + 1);
}

template <typename T>
void MatrixGraph<T>::AddEdge(int from, int to, T&& element) {
    if (m_vtx2idx.find(from) == m_vtx2idx.end())
        MatrixGraph<T>::AddVertex(from);

    if (m_vtx2idx.find(to) == m_vtx2idx.end())
        MatrixGraph<T>::AddVertex(to);

    if (MatrixGraph<T>::CheckEdge(m_vtx2idx.at(from), m_vtx2idx.at(to)))
        return;

    m_graph[m_vtx2idx.at(from)][m_vtx2idx.at(to)] = std::make_pair(true, element);
}
    
template <typename T>
int MatrixGraph<T>::VerticesCount() const {
    return static_cast<int>(m_graph.size());
}

template <typename T>
bool MatrixGraph<T>::CheckEdge(int from, int to) const {
    return m_graph[from][to].first;
}

template <typename T>
void MatrixGraph<T>::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    if (m_vtx2idx.find(vertex) == m_vtx2idx.end())
        return;
    
    for (std::size_t to = 0; to < static_cast<std::size_t>(MatrixGraph<T>::VerticesCount()); to++)
        if (MatrixGraph<T>::CheckEdge(m_vtx2idx.at(vertex), to))
            vertices.push_back(m_idx2vtx[to]);
}

template <typename T>
void MatrixGraph<T>::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    if (m_vtx2idx.find(vertex) == m_vtx2idx.end())
        return;

    for (std::size_t from = 0; from < static_cast<std::size_t>(MatrixGraph<T>::VerticesCount()); from++)
        if (MatrixGraph<T>::CheckEdge(from, m_vtx2idx.at(vertex)))
            vertices.push_back(m_idx2vtx[from]);
}

template <typename T>
void MatrixGraph<T>::DoDFS(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const {
    used[vertex] = true;
    vertices.push_back(m_idx2vtx[vertex]);

    for (std::size_t v = 0; v < static_cast<std::size_t>(MatrixGraph<T>::VerticesCount()); v++)
        if (MatrixGraph<T>::CheckEdge(vertex, v) && !used[v])
            DoDFS(v, vertices, used);
}

template <typename T>
void MatrixGraph<T>::DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
    if (m_vtx2idx.find(vertex) == m_vtx2idx.end())
        return;

    std::vector<bool> used(MatrixGraph<T>::VerticesCount(), false);
    MatrixGraph<T>::DoDFS(m_vtx2idx.at(vertex), vertices, used);
}

template <typename T>
void MatrixGraph<T>::DoBFS(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const {
    used[vertex] = true;

    std::queue<int> q;
    q.push(vertex);

    while (q.size()) {
        int current_vertex = q.front();
        vertices.push_back(m_idx2vtx[current_vertex]);
        q.pop();

        for (std::size_t v = 0; v < static_cast<std::size_t>(MatrixGraph<T>::VerticesCount()); v++)
            if (MatrixGraph<T>::CheckEdge(current_vertex, v) && !used[v]) {
                q.push(v);
                used[v] = true;
            }
    }
}

template <typename T>
void MatrixGraph<T>::BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
    if (m_vtx2idx.find(vertex) == m_vtx2idx.end())
        return;

    std::vector<bool> used(MatrixGraph<T>::VerticesCount(), false);
    MatrixGraph<T>::DoBFS(m_vtx2idx.at(vertex), vertices, used);
}

template <typename T>
void MatrixGraph<T>::TransformToArc(std::vector<std::pair<T, std::pair<int, int>>> &graph) const {
    for (std::size_t from = 0; from < static_cast<std::size_t>(MatrixGraph<T>::VerticesCount()); from++)
        for (std::size_t to = 0; to < static_cast<std::size_t>(MatrixGraph<T>::VerticesCount()); to++)
            if (MatrixGraph<T>::CheckEdge(from, to))
                graph.push_back(std::make_pair(
                    m_graph[from][to].second, 
                    std::make_pair(m_idx2vtx[from], m_idx2vtx[to]))
                );
}

template <typename T> 
void MatrixGraph<T>::ConstructFromArc(std::vector<std::pair<T, std::pair<int, int>>> &graph) {
    for (std::pair<T, std::pair<int, int>> & arc : graph) {
        MatrixGraph<T>::AddEdge(
            arc.second.first, 
            arc.second.second, 
            std::move(arc.first)
        );
    }
}

template <typename T>
MatrixGraph<T>::MatrixGraph(IGraph<T> *_oth) {
    std::vector<std::pair<T, std::pair<int, int>>> arcGraph;
    _oth->TransformToArc(arcGraph);
    MatrixGraph<T>::ConstructFromArc(arcGraph);
}