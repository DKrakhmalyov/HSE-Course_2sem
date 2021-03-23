
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

        m_num_vertices = other.m_vertices;
    }

    PtrsGraph<T>& operator=(PtrsGraph<T> &&other) {
        if (&other == this)
            return *this;

        m_num_vertices = std::move(other.m_vertices);
    }

    virtual int VerticesCount() const {
        return m_num_vertices;
    }


    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) {
        if (from->CheckEdgeTo(to))
            return;

        if (from->Added() == false)
            from->AddVertex();

        if (to->Added() == false)
            to->AddVertex();

        from->AddNextVertex(to, std::move(_obj));
        to->AddPrevVertex(from, std::move(_obj));
    }

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        if (vertex->Added() == false)
            return;

        vertex->GetNextVertices(vertices);
    }

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        if (vertex->Added() == false)
            return;

        vertex->GetPrevVertices(vertices);
    }

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        if (vertex->Added() == false)
            return;

        PtrsGraph<T>::DoDFS(vertex, vertices);
        for (Node<T> *v : vertices)
            v->Unmark();
    }

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        if (vertex->Added() == false)
            return;

        PtrsGraph<T>::DoBFS(vertex, vertices);
        for (Node<T> *v : vertices)
            v->Unmark();
    }

private:

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

    int m_num_vertices = 0;

};

#endif //HOMEWORK_1_PTRSGRAPH_H
