#include <vector>
#include <queue>
#include <unordered_map>
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"


template<typename T>
class ListGraph : public IGraph<T> {
public:
    ListGraph();

    ListGraph(IGraph<T> *_oth);

    ~ListGraph();

    virtual void AddEdge(int from, int to, T &&element);

    virtual int VerticesCount() const;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const;

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const;

    virtual void GetEdges(std::vector<std::pair<std::pair<int,int>, T>> &edges) const;

private:
    size_t _vCount;

    std::vector<std::vector<std::pair<int, T>>> _graph;

    std::unordered_map<int, int> _internalIndex;
    std::unordered_map<int, int> _externalIndex;  

    void _validate(int vertex);

    void _dfs(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const;
};

template<typename T>
ListGraph<T>::ListGraph(): _vCount(0) {};

template<typename T>
ListGraph<T>::ListGraph(IGraph<T> *_oth) {
    _vCount = 0;
    std::vector<std::pair<std::pair<int,int>, T>> edges;
    _oth->GetEdges(edges);
    for (auto &edge : edges) {
        AddEdge(edge.first.first, edge.first.second, std::move(edge.second));
    }
};

template<typename T>
ListGraph<T>::~ListGraph() {
    for (int i = 0; i < _vCount; i++) {
        for (auto to : _graph[i]) {
            ObjectDeleter<T>::Delete(to.second);
        }
    }
}

template<typename T>
void ListGraph<T>::AddEdge(int from, int to, T &&element) {
    _validate(from);
    _validate(to);
    from = _internalIndex[from];
    to = _internalIndex[to];
    _graph[from].emplace_back(to, element);
};

template<typename T>
int ListGraph<T>::VerticesCount() const {
    return _vCount;
};

template<typename T>
void ListGraph<T>::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    for (auto to : _graph[_internalIndex.find(vertex)->second]) {
        vertices.emplace_back(_externalIndex.find(to.first)->second);
    }
};

template<typename T>
void ListGraph<T>::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    for (int from = 0; from < _vCount; from++) {
        for (auto to : _graph[from]) {
            if (_externalIndex.find(to.first)->second == vertex) {
                vertices.emplace_back(_externalIndex.find(from)->second);
            }
        }
    }
};

template<typename T>
void ListGraph<T>::DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
    std::vector<bool> used(_vCount);
    _dfs(_internalIndex.find(vertex)->second, vertices, used);
};

template<typename T>
void ListGraph<T>::BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
    bool *used = new bool[_vCount];
    std::queue<int> queue;
    queue.push(_internalIndex.find(vertex)->second);
    while (!queue.empty()) {
        vertex = queue.front();
        queue.pop();
        vertices.emplace_back(_externalIndex.find(vertex)->second);
        for (auto to : _graph[vertex]) {
            if (!used[to.first]) {
                queue.push(to.first);
                used[to.first] = true;
            }
        }
    }
    delete[] used;
};

template<typename T>
void ListGraph<T>::GetEdges(std::vector<std::pair<std::pair<int,int>, T>> &edges) const {
    int v1, v2;
    for (int i = 0; i < _vCount; i++) {
        for (auto to : _graph[i]) {
            v1 = _externalIndex.find(i)->second, v2 = _externalIndex.find(to.first)->second;
            edges.emplace_back(std::make_pair(v1, v2), ObjectCreater<T>::Create(to.second));
        }
    }
}

template<typename T>
void ListGraph<T>::_validate(int vertex) {
    if (_internalIndex.find(vertex) == _internalIndex.end()) {
        _externalIndex[_vCount] = vertex;
        _internalIndex[vertex] = _vCount++; 
        _graph.resize(_vCount);
    }
}

template<typename T>
void ListGraph<T>::_dfs(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const {
    used[vertex] = true;
    vertices.emplace_back(_externalIndex.find(vertex)->second);
    for (auto to : _graph[vertex]) {
        if (!used[to.first]) {
            _dfs(to.first, vertices, used);
        }
    }
}

#endif //HOMEWORK_1_LISTGRAPH_H
