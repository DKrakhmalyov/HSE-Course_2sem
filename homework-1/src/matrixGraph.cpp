#include "matrixGraph.h"

template <typename T>
MatrixGraph<T>::MatrixGraph() {}

template <typename T>
MatrixGraph<T>::MatrixGraph(IGraph<T> *_oth) {
    
}

template <typename T>
void MatrixGraph<T>::AddEdge(int from, int to, T &&element) {
    AddVertex(from);
    AddVertex(to);
    matrix[toId[from]][toId[to]] = std::make_pair(true, element);
}

template <typename T>
int MatrixGraph<T>::VerticesCount() const {
    return static_cast<int>(toVertex.size());
}

template <typename T>
void MatrixGraph<T>::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    vertices.clear();
    if (toId.find(vertex) != toId.end()) {
        return;
    }
    for (int i = 0; i < VerticesCount(); ++i) {
        if (matrix[toId[vertex]][i].first) {
            vertices.push_back(toVertex[i]);
        }
    }
}

template <typename T>
void MatrixGraph<T>::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    vertices.clear();
    if (toId.find(vertex) != toId.end()) {
        return;
    }
    for (int i = 0; i < VerticesCount(); ++i) {
        if (matrix[i][toId[vertex]].first) {
            vertices.push_back(toVertex[i]);
        }
    }
}

template <typename T>
void MatrixGraph<T>::DeepFirstSearch(int vertex, std::vector<int> &vertices) const {
    vertices.clear();
    if (toId.find(vertex) != toId.end()) {
        return;
    }
    std::vector<bool> used(VerticesCount, false);
    std::functional<void(int)> dfs = [&](int current) {
        int from = toId[current];
        used[from] = true;
        vertices.push_back(current);
        for (int to = 0; to < VerticesCount(); ++to) {
            if (matrix[from][to].first && !used[to]) { 
                dfs(toVertex[to]);
            }
        }
    };
    dfs(vertex);
}

template <typename T>
void MatrixGraph<T>::BreadthFirstSearch(int vertex, std::vector<int> &vertices) const {
    vertices.clear();
    if (toId.find(vertex) != toId.end()) {
        return;
    }
    std::vector<bool> used(VerticesCount, false);
    std::queue<int, std::list<int>> bfs;
    used[toId[vertex]] = true;
    bfs.push(vertex);
    while (!bfs.empty()) {
        int current = bfs.front();
        bfs.pop();
        vertices.push_back(current);
        int from = toId[current];
        for (int to = 0; to < VerticesCount(); ++to) {
            if (matrix[from][to].first && !used[to]) {                
                used[to] = true;
                bfs.push(toVertex[to]);
            }
        }
    }
}

template <typename T>
void MatrixGraph<T>::AddVertex(int vertex) {
    if (toId.find(vertex) != toId.end()) {
        return;
    }
    toVertex.push_back(vertex);
    int sz = static_cast<int>(toVertex.size());
    toId[vertex] = sz - 1;
    matrix.emplace_back();
    for (auto& row: matrix) {
        row.resize(sz);
    }
}