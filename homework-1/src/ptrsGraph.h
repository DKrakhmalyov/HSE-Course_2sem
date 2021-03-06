
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {

public:
    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) {
        from->next.push_back(PtrsEdge<T>{from, to, std::move(_obj)});
        to->prev.push_back(PtrsEdge<T>{from, to, std::move(_obj)});
        allVertices.insert(from);
        allVertices.insert(to);
    };

    PtrsGraph() = default;

    virtual int VerticesCount() const { 
        return allVertices.size();
    };

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        for(auto edge : vertex->next) {
            vertices.push_back(edge.to);
        }
    };

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        for(auto edge : vertex->prev) {
            vertices.push_back(edge.from);
        }
    };

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        std::map<Node<T> *, bool> used;
        dfs(vertex, vertices, used);
    };

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        std::map<Node<T> *, bool> used;
        std::queue<Node<T> *> q;
        q.push(vertex);
        used[vertex] = true;
        while(!q.empty()) {
            Node<T> *from = q.front();
            q.pop();
            vertices.push_back(q.front());
            std::vector<Node<T> *> next;
            GetNextVertices(vertex, next);
            for(auto to : next) {
                if(!used[to]) {
                    used[to] = true;
                    q.push(to);
                }
            }
        }
    };
    
private:
    std::set<Node<T> *> allVertices;

    void dfs(Node<T> *vertex, std::vector<Node<T> *> &vertices, std::map<Node<T> *, bool> &used) const {
        used[vertex] = true;
        vertices.push_back(vertex);
        std::vector<Node<T> *> next;
        GetNextVertices(vertex, next);
        for(auto to : next) {
            if(!used[to]) {
                dfs(to, vertices, used);
            }
        }
    } 
};

#endif //HOMEWORK_1_PTRSGRAPH_H
