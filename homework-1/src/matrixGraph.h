
#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H

#include <queue>
#include <unordered_map>

#include "../graph.h"

template<typename T = void>
class MatrixGraph : public IGraph<T> {
public:
    MatrixGraph();

    MatrixGraph(IGraph<T> *_oth);

    ~MatrixGraph();

    virtual void AddEdge(int from, int to, T &&element);

    virtual int VerticesCount() const;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const;

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const;

    virtual void GetEdges(std::vector<std::pair<std::pair<int,int>, T>> &edges) const;

private:
    size_t _vCount;

    std::vector<std::vector<T>> _weight;
    std::vector<std::vector<bool>> _isConnected;

    std::unordered_map<int, int> _internalIndex;
    std::unordered_map<int, int> _externalIndex;

    void _validate(int vertex);

    void _dfs(int vertex, std::vector<int> &vertices, bool* used) const;
};

template<typename T>
MatrixGraph<T>::MatrixGraph(): _vCount(0) {};

template<typename T>
MatrixGraph<T>::MatrixGraph(IGraph<T> *_oth) {
    _vCount = 0;
    std::vector<std::pair<std::pair<int,int>, T>> edges;
    _oth->GetEdges(edges);
    for (auto edge : edges) {
        AddEdge(edge.first.first, edge.first.second, std::forward<T>(edge.second));
    }
};

template<typename T>
MatrixGraph<T>::~MatrixGraph() {
    for (int i = 0; i < _vCount; i++) {
        for (int j = 0; j < _vCount; j++) {
            if (_isConnected[i][j]) {
                ObjectDeleter<T>::Delete(_weight[i][j]);
            }
        }
    }
}

template<typename T>
void MatrixGraph<T>::AddEdge(int from, int to, T &&element) {
    _validate(from);
    _validate(to);
    from = _internalIndex[from];
    to = _internalIndex[to];
    _isConnected[from][to] = true;
    _weight[from][to] = std::forward<T>(element);
};

template<typename T>
int MatrixGraph<T>::VerticesCount() const {
    return _vCount;
};

template<typename T>
void MatrixGraph<T>::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    vertex = _internalIndex.find(vertex)->second;
    for (int to = 0; to < _vCount; to++) {
        if (_isConnected[vertex][to]) {
            vertices.push_back(_externalIndex.find(to)->second);
        }
    }
};

template<typename T>
void MatrixGraph<T>::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    vertex = _internalIndex.find(vertex)->second;
    for (int to = 0; to < _vCount; to++) {
        if (_isConnected[to][vertex]) {
            vertices.push_back(_externalIndex.find(to)->second);
        }
    }
};

template<typename T>
void MatrixGraph<T>::DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
    bool *used = new bool[_vCount];
    _dfs(_internalIndex.find(vertex)->second, vertices, used);
    delete[] used;
};

template<typename T>
void MatrixGraph<T>::BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
    bool *used = new bool[_vCount];
    std::queue<int> queue;
    queue.push(_internalIndex.find(vertex)->second);
    while (!queue.empty()) {
        vertex = queue.front();
        queue.pop();
        vertices.push_back(_externalIndex.find(vertex)->second);
        for (int to = 0; to < _vCount; to++) {
            if (_isConnected[vertex][to] && !used[to]) {
                queue.push(to);
                used[to] = true;
            }
        }
    }
    delete[] used;
};

template<typename T>
void MatrixGraph<T>::GetEdges(std::vector<std::pair<std::pair<int,int>, T>> &edges) const {
    int v1, v2;
    for (int i = 0; i < _vCount; i++) {
        for (int j = 0; j < _vCount; j++) {
            if (_isConnected[i][j]) {
                v1 = _externalIndex.find(i)->second, v2 = _externalIndex.find(j)->second;
                edges.push_back({{v1, v2}, ObjectCreater<T>::Create(_weight[i][j])});
            }
        }
    }
}


template<typename T>
void MatrixGraph<T>::_validate(int vertex) {
    if (_internalIndex.find(vertex) == _internalIndex.end()) {
        _externalIndex[_vCount] = vertex;
        _internalIndex[vertex] = _vCount++;
        _weight.push_back({});
        _isConnected.push_back({});
        for (int i = 0; i < _vCount; i++) {
            _weight[i].resize(_vCount);
            _isConnected[i].resize(_vCount);
        }
    }

}

template<typename T>
void MatrixGraph<T>::_dfs(int vertex, std::vector<int> &vertices, bool* used) const {
    used[vertex] = true;
    vertices.push_back(_externalIndex.find(vertex)->second);
    for (int to = 0; to < _vCount; to++) {
        if (_isConnected[vertex][to] && !used[to]) {
            _dfs(to, vertices, used);
        }
    }
}

#endif //HOMEWORK_1_MATRIXGRAPH_H
