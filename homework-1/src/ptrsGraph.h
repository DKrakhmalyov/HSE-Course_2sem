#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"
#include <unordered_set>

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {
public:

     virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) {
        from->nodes.emplace_back(to, std::forward<T>(_obj));
        vrtcs.insert(from);
        vrtcs.insert(to);
    };

    PtrsGraph() {};

    virtual int VerticesCount() const { return vrtcs.size(); };

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        for (auto const &[i, j] : vertex->nodes) 
        vertices.push_back(i);
    };

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        for (auto i : vrtcs)
            if (std::find_if(i->nodes.begin(), i->nodes.end(), [vertex](const std::pair<Node<T> *, T> p) {
                return p.first == vertex;
            }) != i->nodes.end())
                vertices.push_back(i);
    };

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        std::unordered_map<Node<T> *, bool> used;
        auto dfs = [&used, &vertices, this](Node<T> *vrtx, auto &dfs_) mutable -> void {
            used[vrtx] = true;
            vertices.push_back(vrtx);
            std::vector<Node<T> *> newbound;
            GetNextVertices(vrtx, newbound);
            for (auto v : newbound) {
                if (!used[v])
                    dfs_(v, dfs_);
            }
        };
        dfs(vertex, dfs);
    };

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        std::unordered_map<Node<T> *, bool> used;
        std::queue<Node<T> *> q;
        q.push(vertex);
        used[vertex] = true;
        while (!q.empty()) {
            std::vector<Node<T> *> newbound;
            GetNextVertices(q.front(), newbound);
            for (auto i : newbound)
                if (!used[i])
                    q.push(i), used[i] = true;
            vertices.push_back(q.front());
            q.pop();
        }
    };
    private:
    std::unordered_set<Node<T> *> vrtcs;
};

#endif //HOMEWORK_1_PTRSGRAPH_H
