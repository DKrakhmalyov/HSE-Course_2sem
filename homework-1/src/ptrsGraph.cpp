#include "ptrsGraph.h"

template <typename T>
int PtrsGraph<T>::VerticesCount() const {
    return static_cast<int>(m_vertices.size());
}

template <typename T>
void PtrsGraph<T>::AddVertex(Node<T> *vertex) {
    if (m_vertices.find(vertex) != m_vertices.end())
        return;

    m_vertices.insert(vertex);
}

template <typename T>
void PtrsGraph<T>::AddEdge(Node<T> *from, Node<T> *to, T &&element) {
    if (from->CheckEdgeTo(to))
        return;

    if (m_vertices.find(from) == m_vertices.end())
        PtrsGraph<T>::AddVertex(from);

    if (m_vertices.find(to) == m_vertices.end())
        PtrsGraph<T>::AddVertex(to);


    from->AddNextVertex(to, std::move(element));
}

template <typename T>
void PtrsGraph<T>::GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
    if (m_vertices.find(vertex) == m_vertices.end())
        return;

    vertex->GetNextVertices(vertices);
}

template <typename T>
void PtrsGraph<T>::GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
    if (m_vertices.find(vertex) == m_vertices.end())
        return;

    for (Node<T>* v : m_vertices)
        if (v->CheckEdgeTo(vertex))
            vertices.push_back(v);
}

template <typename T>
void PtrsGraph<T>::DoDFS(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
    vertex->Mark();
    vertices.push_back(vertex);

    std::vector<Node<T> *> next_vertices;
    vertex->GetNextVertices(next_vertices);

    for (Node<T> *v : next_vertices)
        if (!v->Marked())
            DoDFS(v, vertices);
}

template <typename T>
void PtrsGraph<T>::DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
    if (m_vertices.find(vertex) == m_vertices.end())
        return;

    PtrsGraph<T>::DoDFS(vertex, vertices);
    PtrsGraph<T>::UnmarkVertices();
}

template <typename T>
void PtrsGraph<T>::DoBFS(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
    vertex->Mark();

    std::queue<Node<T> *> q;
    q.push(vertex);

    while (q.size()) {
        Node<T> *current_vertex = q.front();
        vertices.push_back(current_vertex);
        q.pop();

        std::vector<Node<T> *> next_vertices;
        PtrsGraph<T>::GetNextVertices(current_vertex, next_vertices);        

        for (Node<T> *v : next_vertices)
            if (!v->Marked()) {
                q.push(v);
                v->Mark();
            }
    }
}

template <typename T>
void PtrsGraph<T>::BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
    if (m_vertices.find(vertex) == m_vertices.end())
        return;

    PtrsGraph<T>::DoBFS(vertex, vertices);
    PtrsGraph<T>::UnmarkVertices();
}

template <typename T>
void PtrsGraph<T>::UnmarkVertices() const {
    for (Node<T> *vertex : m_vertices)
        vertex->Unmark();
}