
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>


template<typename T>
class ListGraph : public IGraph<T> {
public:
    virtual void AddEdge(int from, int to, T &&element);

    ListGraph() = default;;

    ListGraph(IGraph<T> *_oth) {};

    [[nodiscard]] virtual int VerticesCount() const;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const;

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const;
private:
    std::unordered_map<int, std::vector<std::pair<int, T>>> _g;
    std::unordered_map<int, std::vector<std::pair<int, T>>> _gt;
    void _dfs(int vertex, std::unordered_set<int> used, std::vector<int> &vertices) const;
};

#endif //HOMEWORK_1_LISTGRAPH_H
