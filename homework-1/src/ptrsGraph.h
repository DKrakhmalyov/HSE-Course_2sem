
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {

public:

    PtrsGraph() {};
    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) {
        if (!from->flag()){
            ptrsg++;
            from->reflag();
            from->renum(sch);
            sch++;
        }
        if (to->flag()){
            ptrsg++;
            to->reflag();
            to->renum(sch);
            sch++;
        }
        from->AddEdge(to, std::forward<T>(_obj));
        to->AddEdgeb(from, std::forward<T>(_obj));
    };

    virtual int VerticesCount() const {     
        return ptrsg;
    };

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        vertex->GetNextVertices(vertices);
    };

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        vertex->GetPrevVertices(vertices);
    };

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        std::vector<bool> used(ptrsg, false);
        vertex->dfs(vertices, used);
    };

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        std::vector<bool> used(ptrsg, false);
        std::queue<Node<T>*> qu;
        vertex->bfs(vertices, used, qu);
    };

private:
    int ptrsg = 0;
    int sch = 0;
};

#endif //HOMEWORK_1_PTRSGRAPH_H
