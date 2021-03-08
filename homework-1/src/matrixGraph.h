
#ifndef HOMEWORK_1_MATRIXGRAPH_H
#define HOMEWORK_1_MATRIXGRAPH_H


#include "../graph.h"
#include <vector>
#include <unordered_set>
#include <cassert>
#include <queue>

template<typename T = void>
class MatrixGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element);

    MatrixGraph() = default;

    MatrixGraph(IGraph<T> *_oth) {};

    [[nodiscard]] virtual int VerticesCount() const;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const;

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const;
protected:
    std::vector<std::vector<std::pair<bool, T>>> _g;
    std::vector<std::vector<std::pair<bool, T>>> _gt;

    std::unordered_set<int> _vertices;

    void _dfs(int vertex, std::unordered_set<int> &used, std::vector<int> &vertices) const;
};

#endif //HOMEWORK_1_MATRIXGRAPH_H
