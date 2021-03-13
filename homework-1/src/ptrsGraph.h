
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"
#include <unordered_set>
#include <queue>

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {
public:
    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) {
        from->next.push_back(to);
        from->weights.push_back(std::forward<T>(_obj));
        if (!nodes.contains(from)) {
            nodes.insert(from);
        }
        if (!nodes.contains(to)) {
            nodes.insert(to);
        }
    };

    PtrsGraph() {};

    virtual int VerticesCount() const { 
        return nodes.size();
    };

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        vertices = vertex->next;
    };

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        vertices.clear();
        for (auto &from : nodes) {
            bool is_prev = false;
            for (auto &to : from->next) {
                if (to == vertex) {
                    is_prev = true;
                }
            }
            if (is_prev) {
                vertices.push_back(from);
            }
        }
    };

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        std::unordered_set<Node<T>*> used_nodes;
        dfs(vertex, vertices, used_nodes);
    };

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        std::unordered_set<Node<T>*> used_nodes;
        std::queue<Node<T>*> q;
        q.push(vertex);
        while(!q.empty()) {
            vertex = q.front();
            q.pop();
            vertices.push_back(vertex);
            for (auto &to : vertex->next) {
                if (!used_nodes.contains(to)) {
                    q.push(to);
                    used_nodes.insert(to);
                }
            }
        }
    };
private:
    std::unordered_set<Node<T>*> nodes;
    void dfs(Node<T> *vertex, std::vector<Node<T> *> &vertices, std::unordered_set<Node<T>*>& used_nodes) const {
        used_nodes.insert(vertex);
        vertices.push_back(vertex);
        for (auto &to : vertex->next) {
            if (!used_nodes.contains(to)) {
                dfs(to, vertices, used_nodes);
            }
        }
    }
};

#endif //HOMEWORK_1_PTRSGRAPH_H
