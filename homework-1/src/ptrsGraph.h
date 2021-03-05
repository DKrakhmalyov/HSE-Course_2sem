
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "node.cpp"
#include "../graph.h"

template<typename T>
class PtrsGraph : public IPtrsGraph<T> {

public:

    PtrsGraph() = default;    

    PtrsGraph(const PtrsGraph<T> &other) = default;

    PtrsGraph(PtrsGraph<T> &&other) = default;

    PtrsGraph<T>& operator=(const PtrsGraph<T> &other);

    PtrsGraph<T>& operator=(PtrsGraph<T> &&other);

    virtual ~PtrsGraph() = default;

    virtual int VerticesCount() const;

    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj);

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const;

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const;

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const ;

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const ;

private:

    void UnmarkVertices() const;

    void AddVertex(Node<T> *vertex);

    virtual void DoDFS(Node<T> *vertex, std::vector<Node<T> *> &vertices) const;

    virtual void DoBFS(Node<T> *vertex, std::vector<Node<T> *> &vertices) const;

private:

    std::set<Node<T> *, typename Node<T>::less> m_vertices;
};

#endif //HOMEWORK_1_PTRSGRAPH_H
