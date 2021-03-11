
#ifndef HOMEWORK_1_PTRSGRAPH_H
#define HOMEWORK_1_PTRSGRAPH_H

#include "node.h"
#include "../graph.h"
#include <utility>

template<typename T = void>
class PtrsGraph : public IPtrsGraph<T> {

public:
    PtrsGraph(): _vCount(0) {};

    ~PtrsGraph() {
        for (size_t i = 0; i < _vCount; i++) {
            delete nodes[i];
        }
    }

    virtual void AddEdge(Node<T> *from, Node<T> *to, T &&_obj) {
        from->addEdge(to, std::forward<T>(_obj));
        if (_getPosition(from) == -1) {
            nodes.push_back(from);
            _vCount++;
        }
        if (_getPosition(to) == -1) {
            nodes.push_back(to);
            _vCount++;
        }
    };

    virtual int VerticesCount() const {
        return _vCount;
    };

    virtual void GetNextVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        vertices = vertex->next;
    };

    virtual void GetPrevVertices(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        for (size_t i = 0; i < _vCount; i++) {
            bool connected = false;
            for (size_t j = 0; j < nodes[i]->next.size(); j++) {
                if (nodes[i]->next[j] == vertex) {
                    connected = true;
                }
            }
            if (connected) {
                vertices.push_back(nodes[i]);
            }
        }
    };

    virtual void DeepFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        std::vector<int> used(_vCount);
        _dfs(vertex, vertices, used);
    };

    virtual void BreadthFirstSearch(Node<T> *vertex, std::vector<Node<T> *> &vertices) const {
        bool *used = new bool[_vCount];
        std::queue<Node<T>*> queue;
        queue.push(vertex);
        while (!queue.empty()) {
            vertex = queue.front();
            queue.pop();
            vertices.push_back(vertex);
            for (auto node : vertex->next) {
                int to = _getPosition(node);
                if (!used[to]) {
                    queue.push(node);
                    used[to] = true;
                }
            }
        }
        delete[] used;
    };

private:
    size_t _vCount;

    std::vector<Node<T>*> nodes;

    int _getPosition(Node<T> *node) const {
        size_t position;
        bool contains = false;
        for (size_t i = 0; i < _vCount; i++) {
            if (nodes[i] == node) {
                contains = true;
                position = i;
            }
        }
        if (!contains) {
            return -1;
        }
        return position;
    }

    virtual void _dfs(Node<T> *vertex, std::vector<Node<T> *> &vertices, std::vector<int> &used) const {
        int pos = _getPosition(vertex);
        used[pos] = true;
        vertices.push_back(vertex);
        for (auto node : vertex->next) {
            int to = _getPosition(node);
            if (!used[to]) {
                _dfs(node, vertices, used);
            }
        }
    };
};

#endif //HOMEWORK_1_PTRSGRAPH_H
