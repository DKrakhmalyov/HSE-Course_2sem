
#ifndef HOMEWORK_1_LISTGRAPH_H
#define HOMEWORK_1_LISTGRAPH_H

#include "../graph.h"

template<typename T>
class ListGraph : public IGraph<T> {

public:

    ListGraph() = default;

    ListGraph(IGraph<T> *_oth);

    virtual ~ListGraph() = default;

    virtual bool CheckEdge(int from, int to) const;

    virtual void AddEdge(int from, int to, T &&element);

    virtual int VerticesCount() const;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const;

    virtual void DeepFirstSearch(int vertex, std::vector<int> &vertices) const;

    virtual void BreadthFirstSearch(int vertex, std::vector<int> &vertices) const;

    virtual void TransformToArc(std::vector<std::pair<T, std::pair<int, int>>> &graph) const;

private:

    virtual void GetVertices(std::vector<int> &vertices) const;

    virtual void DoDFS(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const;

    virtual void DoBFS(int vertex, std::vector<int> &vertices, std::vector<bool> &used) const;

    virtual void ConstructFromArc(std::vector<std::pair<T, std::pair<int, int>>> &graph);

private:

    std::unordered_map<int, std::vector<std::pair<int, T>>> m_graph;
    std::unordered_map<int, std::vector<std::pair<int, T>>> m_reversed_graph;

    std::vector<bool> m_used;
};


#endif //HOMEWORK_1_LISTGRAPH_H
