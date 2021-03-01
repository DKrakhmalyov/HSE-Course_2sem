
#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H


#include "../graph.h"

template<typename T = void>
class MatrixGraph : public IGraph<T> {
public:
    MatrixGraph(): _vCount(0) {};

    MatrixGraph(IGraph<T> *_oth) {};

    virtual void AddEdge(int from, int to, T &&element) {
        if (from >= _vCount || to >= _vCount || from < 0 || to < 0) {
            throw "Error: incorrect node";
        }
        _graph[from][to] = element;
        _isConnected[from][to] = true;
    };

    void AddNode() {
        _graph.resize(_graph.size() + 1);
        _isConnected.resize(_graph.size() + 1);
        _vCount++;
        for (size_t i = 0; i < _vCount; i++) {
            _graph[i].resize(_vCount);
            _isConnected[i].resize(_vCount);
        }
    }

    virtual int VerticesCount() const {
         return _vCount; 
    };

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        for (size_t i = 0; i < _vCount; i++) {
            if (_isConnected[vertex][i]) {
                vertices.push_back(i);
            }
        }
    };

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const  {
        for (size_t i = 0; i < _vCount; i++) {
            if (_isConnected[i][vertex]) {
                vertices.push_back(i);
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
            for (size_t to = 0; to < _vCount; to++) {
                if (_isConnected[vertex][to] && !used[to]) {
                    queue.push(to);
                    used[to] = true;
                }
            }
        }
        delete[] used;
    };

private:
    size_t _vCount;

    std::vector<std::vector<T>> _graph;
    std::vector<std::vector<bool>> _isConnected;

    void _dfs(int vertex, std::vector<int> &vertices, bool* used) const {
        used[vertex] = true;
        vertices.push_back(vertex);
        for (size_t to = 0; to < _vCount; to++) {
            if (_isConnected[vertex][to] && !used[to]) {
                _dfs(to, vertices, used);
            }
        }
    }
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
