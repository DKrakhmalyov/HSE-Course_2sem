
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"
#include <utility>
#include <unordered_set>

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {

public:
    PtrsGraph(): _vCount(0) {};

    ~PtrsGraph() = default;

    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) {
        from->addEdge(to, std::forward<T>(_obj));
        if (!from->added) {
            _vCount++;
            from->added = 1;
        }
        if (!to->added) {
            _vCount++;
            to->added = 1;
        }
    };

    virtual int VerticesCount() const {
        return _vCount;
    };

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        vertices = vertex->next;
    };

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        vertices = vertex->prev;
    };

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        std::unordered_set<Node<T>*> used;
        _dfs(vertex, vertices, used);
    };

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        std::unordered_set<Node<T>*> used;
        std::queue<Node<T>*> queue;
        queue.push(vertex);
        while (!queue.empty()) {
            vertex = queue.front();
            queue.pop();
            vertices.emplace_back(vertex);
            for (auto node : vertex->next) {
                if (!used.contains(node)) {
                    queue.push(node);
                    used.insert(node);
                }
            }
        }
    };

private:
    size_t _vCount;

    virtual void _dfs(Node<T> *vertex, std::vector<Node<T> *> &vertices, std::unordered_set<Node<T>*> &used) const {
        used.insert(vertex);
        vertices.emplace_back(vertex);
        for (auto node : vertex->next) {
            if (!used.contains(node)) {
                _dfs(node, vertices, used);
            }
        }
    };
};

#endif //HOMEWORK_1_PTRSGRAPH_H
