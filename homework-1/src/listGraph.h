#include <vector>
#include <queue>
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"


template<typename T>
class ListGraph : public IGraph<T> {
public:
    ListGraph(): _vCount(0) {};

    ListGraph(IGraph<T> *_oth) {};

    virtual void AddEdge(int from, int to, T &&element) {
        if (from >= _vCount || to >= _vCount || from < 0 || to < 0) {
            throw "Error: incorrect node";
        }
        _graph[from].push_back({to, element});
    };

    void AddNode() {
        _graph.resize(_graph.size() + 1);
        _vCount++;
    }

    virtual int VerticesCount() const {
        return _vCount;
    };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for (auto to : _graph[vertex]) {
            vertices.push_back(to.first);
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        for (size_t from = 0; from < _vCount; from++) {
            for (auto to : _graph[from]) {
                if (to.first == vertex) {
                    vertices.push_back(from);
                }
            }
        }
    };

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
        bool *used = new bool[_vCount];
        _dfs(vertex, vertices, used);
        delete[] used;
    };

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
        bool *used = new bool[_vCount];
        std::queue<int> queue;
        queue.push(vertex);
        while (!queue.empty()) {
            vertex = queue.front();
            queue.pop();
            vertices.push_back(vertex);
            for (auto to : _graph[vertex]) {
                if (!used[to.first]) {
                    queue.push(to.first);
                    used[to.first] = true;
                }
            }
        }
        delete[] used;
    };

private:
    size_t _vCount;
    
    std::vector<std::vector<std::pair<int, T>>> _graph;

    void _dfs(int vertex, std::vector<int> &vertices, bool* used) const {
        used[vertex] = true;
        vertices.push_back(vertex);
        for (auto to : _graph[vertex]) {
            if (!used[to.first]) {
                _dfs(to.first, vertices, used);
            }
        }
    }
};


#endif //HOMEWORK_1_LISTGRAPH_H
