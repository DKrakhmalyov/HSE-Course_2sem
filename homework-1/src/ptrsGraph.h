
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {
    int size_ = 0;

public:
    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) override {
        if (from->Empty())
            ++size_;
        if (to->Empty())
            ++size_;
        from->AddNode(to, std::forward<T>(_obj));
        to->AddPrevNode(from);
    };

    PtrsGraph() {};

    virtual int VerticesCount() const override { return size_; };

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override {
        vertex->GetNextNodes(vertices);
    };

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override {
        vertex->GetPrevNodes(vertices);
    };

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override {
        std::unordered_set<Node<T> *> used;
        auto dfs = [this, &used, &vertices](Node<T> *vertex, auto const &dfs) {
            used.insert(vertex);
            vertices.push_back(vertex);
            std::vector<Node<T> *> next_vertices;
            GetNextVertices(vertex, next_vertices);
            if (next_vertices.empty())
                return;
            for (auto i : next_vertices) {
                if (!used.contains(i))
                    dfs(i, dfs);
            }
        };
        dfs(vertex, dfs);
    };

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const override {
        std::unordered_set<Node<T> *> used;
        std::queue<Node<T> *> queue;
        std::vector<Node<T> *> next_vertices;
        queue.push(vertex);
        while (!queue.empty()) {
            auto now = queue.front();
            vertices.push_back(now);
            queue.pop();
            next_vertices.clear();
            GetNextVertices(now, next_vertices);
            if (next_vertices.empty())
                continue;
            for (auto i : next_vertices) {
                if (!used.contains(i)) {
                    used.insert(i);
                    queue.push(i);
                }
            }
        }
    };
};

#endif //HOMEWORK_1_PTRSGRAPH_H
