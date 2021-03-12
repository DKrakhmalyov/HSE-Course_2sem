
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"
#include <unordered_set>

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {
private:
    std::unordered_set<Node<T> *> vrtcs;

public:
    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) {
        from->nodes.emplace_back(to, std::forward<T>(_obj));
        vrtcs.insert(from);
        vrtcs.insert(to);
    };

    PtrsGraph() {};

    virtual int VerticesCount() const { return vrtcs.size(); };

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        for (auto const &[v, w] : vertex->nodes) vertices.push_back(v);
    };

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        for (auto v : vrtcs)
            if (std::find_if(v->nodes.begin(), v->nodes.end(), [vertex](const std::pair<Node<T> *, T> p) {
                return p.first == vertex;
            }) != v->nodes.end())
                vertices.push_back(v);
    };

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        std::unordered_map<Node<T> *, bool> used;
        auto dfs = [&used, &vertices, this](Node<T> *vrtx, auto &dfs_) mutable -> void {
            used[vrtx] = true;
            vertices.push_back(vrtx);
            std::vector<Node<T> *> next;
            GetNextVertices(vrtx, next);
            for (auto v : next) {
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
            std::vector<Node<T> *> next;
            GetNextVertices(q.front(), next);
            for (auto v : next)
                if (!used[v])
                    q.push(v), used[v] = true;
            vertices.push_back(q.front());
            q.pop();
        }
    };
};

#endif //HOMEWORK_1_PTRSGRAPH_H
