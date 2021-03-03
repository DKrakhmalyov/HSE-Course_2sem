#include "matrixGraph.h"

template <typename T>
void MatrixGraph<T>::AddEdge(int from, int to, T&& element) {
    if (std::max(from, to) >= MatrixGraph<T>::VerticesCount()) {
        m_graph.resize(std::max(from, to) + 1);
        for (std::size_t i = 0; i < static_cast<std::size_t>(MatrixGraph<T>::VerticesCount()); i++)
            m_graph[i].resize(std::max(from, to) + 1);
    }

    if (MatrixGraph<T>::CheckEdge(from, to))
        return;

    m_graph[from][to] = element;
}
    
template <typename T>
int MatrixGraph<T>::VerticesCount() const {
    return static_cast<int>(m_graph.size());
}

template <typename T>
bool MatrixGraph<T>::CheckEdge(int from, int to) const {
    if (std::max(from, to) >= MatrixGraph<T>::VerticesCount())
        return false;
    return bool(m_graph[from][to] != T());
}

template <typename T>
void MatrixGraph<T>::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    for (std::size_t to = 0; to < static_cast<std::size_t>(MatrixGraph<T>::VerticesCount()); to++)
        if (MatrixGraph<T>::CheckEdge(vertex, static_cast<int>(to)))
            vertices.push_back(to);
}

template <typename T>
void MatrixGraph<T>::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    for (std::size_t from = 0; from < static_cast<std::size_t>(MatrixGraph<T>::VerticesCount()); from++)
        if (MatrixGraph<T>::CheckEdge(from, vertex))
            vertices.push_back(from);
}

template <typename T>
void MatrixGraph<T>::DoDFS(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const {
    used[vertex] = true;
    vertices.push_back(vertex);

    for (std::size_t v = 0; v < static_cast<std::size_t>(MatrixGraph<T>::VerticesCount()); v++)
        if (MatrixGraph<T>::CheckEdge(vertex, v) && !used[v])
            DoDFS(v, vertices, used);
}

template <typename T>
void MatrixGraph<T>::DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
    std::vector<bool> used(MatrixGraph<T>::VerticesCount(), false);
    MatrixGraph<T>::DoDFS(vertex, vertices, used);
}

template <typename T>
void MatrixGraph<T>::DoBFS(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const {
    used[vertex] = true;

    std::queue<int> q;
    q.push(vertex);

    while (q.size()) {
        int current_vertex = q.front();
        vertices.push_back(current_vertex);
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
    std::vector<bool> used(MatrixGraph<T>::VerticesCount(), false);
    MatrixGraph<T>::DoBFS(vertex, vertices, used);
}

template <typename T>
void MatrixGraph<T>::TransformToArc(std::vector<std::pair<T, std::pair<int, int>>> &graph) const {
    for (std::size_t from = 0; from < static_cast<std::size_t>(MatrixGraph<T>::VerticesCount()); from++)
        for (std::size_t to = 0; to < static_cast<std::size_t>(MatrixGraph<T>::VerticesCount()); to++)
            if (MatrixGraph<T>::CheckEdge(from, to))
                graph.push_back(std::make_pair(m_graph[from][to], std::make_pair(from, to)));
}

template <typename T> 
void MatrixGraph<T>::ConstructFromArc(std::vector<std::pair<T, std::pair<int, int>>> &graph) {
    for (std::pair<T, std::pair<int, int>> & arc : graph)
        MatrixGraph<T>::AddEdge(arc.second.first, arc.second.second, std::move(arc.first));
}

template <typename T>
MatrixGraph<T>::MatrixGraph(IGraph<T> *_oth) {
    std::vector<std::pair<T, std::pair<int, int>>> arcGraph;
    _oth->TransformToArc(arcGraph);
    MatrixGraph<T>::ConstructFromArc(arcGraph);
}