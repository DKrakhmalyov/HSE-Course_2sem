
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"

template<typename T>
class PtrsGraph : public IPtrsGraph<T> {

public:

    PtrsGraph() = default;    

    virtual ~PtrsGraph() = default;

    PtrsGraph(const PtrsGraph<T> &other) = default;

    PtrsGraph(PtrsGraph<T> &&other) = default;

    PtrsGraph<T>& operator=(const PtrsGraph<T> &other) {
        if (&other == this)
            return *this;

        m_vertices = other.m_vertices;
    }

    PtrsGraph<T>& operator=(PtrsGraph<T> &&other) {
        if (&other == this)
            return *this;

        m_vertices = std::move(other.m_vertices);
    }

    virtual int VerticesCount() const {
        return static_cast<int>(m_vertices.size());
    }


    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) {
        if (from->CheckEdgeTo(to))
            return;

        if (m_vertices.find(from) == m_vertices.end())
            PtrsGraph<T>::AddVertex(from);

        if (m_vertices.find(to) == m_vertices.end())
            PtrsGraph<T>::AddVertex(to);


        from->AddNextVertex(to, std::move(_obj));
    }

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        if (m_vertices.find(vertex) == m_vertices.end())
            return;

        vertex->GetNextVertices(vertices);
    }

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        if (m_vertices.find(vertex) == m_vertices.end())
            return;

        for (Node<T>* v : m_vertices)
            if (v->CheckEdgeTo(vertex))
                vertices.push_back(v);
    }

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        if (m_vertices.find(vertex) == m_vertices.end())
            return;

        PtrsGraph<T>::DoDFS(vertex, vertices);
        PtrsGraph<T>::UnmarkVertices();
    }

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        if (m_vertices.find(vertex) == m_vertices.end())
            return;

        PtrsGraph<T>::DoBFS(vertex, vertices);
        PtrsGraph<T>::UnmarkVertices();
    }

private:

    void UnmarkVertices() const {
        for (Node<T> *vertex : m_vertices)
            vertex->Unmark();
    }

    void AddVertex(Node<T> *vertex) {
        if (m_vertices.find(vertex) != m_vertices.end())
            return;

        m_vertices.insert(vertex);
    }

    virtual void DoDFS(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        vertex->Mark();
        vertices.push_back(vertex);

        std::vector<Node<T> *> next_vertices;
        vertex->GetNextVertices(next_vertices);

        for (Node<T> *v : next_vertices)
            if (!v->Marked())
                DoDFS(v, vertices);
    }

    virtual void DoBFS(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
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

private:

    std::set<Node<T> *, typename Node<T>::less> m_vertices;
};

#endif //HOMEWORK_1_PTRSGRAPH_H
