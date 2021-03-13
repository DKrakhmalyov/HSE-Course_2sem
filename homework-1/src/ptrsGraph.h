
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {

public:

    PtrsGraph() {};
    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) {
        ptrsg.insert(from);
        ptrsg.insert(to);
        from->AddEdge(to, std::forward<T>(_obj));
        to->AddEdgeb(from, std::forward<T>(_obj));
    };

    virtual int VerticesCount() const {     
        return ptrsg.size();
    };

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        vertex->GetNextVertices(vertices);
    };

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        vertex->GetPrevVertices(vertices);
    };

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        std::unordered_map<Node<T>*, bool> used;
        for(auto i: ptrsg){
            used.insert({i, false});
        }
        vertex->dfs(vertices, used);
    };

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        std::unordered_map<Node<T>*, bool> used;
        std::queue<Node<T>*> qu;
        for(auto iter = ptrsg.begin(); iter != ptrsg.end(); ++iter){
            used[*iter] = false;
        }
        vertex->bfs(vertices, used, qu);
    };

private:
    std::unordered_set<Node<T>*> ptrsg;
};

#endif //HOMEWORK_1_PTRSGRAPH_H
